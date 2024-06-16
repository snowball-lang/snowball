
#include "compiler/ctx.h"
#include "compiler/utils/hash.h"
#include "compiler/backend/drivers.h"
#include "compiler/backend/llvm/builder.h"

#include "app/cli.h"
#include "compiler/globals.h"

#include <llvm/Bitcode/BitcodeWriter.h>

namespace snowball {
namespace backend {

bool LLVMBuilder::link(const Ctx& ctx, std::vector<std::filesystem::path>& paths, std::filesystem::path output) {  
  auto obj_path = driver::get_workspace_path(ctx, driver::WorkSpaceType::Obj);
  // Get all the llvm bitcode files and link them
  auto builder_ctx = std::make_shared<llvm::LLVMContext>();
  auto libroot_path = (obj_path / utils::hash::hashString(".libroot")).string() + ".bc";
  auto buffer = llvm::MemoryBuffer::getFile(libroot_path);
  sn_assert(buffer, "Failed to open file: " + libroot_path);
  auto libroot = llvm::parseBitcodeFile(buffer.get()->getMemBufferRef(), *builder_ctx);
  llvm::Linker ld(*libroot.get());
  for (auto& path : paths) {
    if (path == libroot_path) {
      continue;
    }
    buffer = llvm::MemoryBuffer::getFile(path.string());
    sn_assert(buffer, "Failed to open file: " + path.string());
    auto module = llvm::parseBitcodeFile(buffer.get()->getMemBufferRef(), *builder_ctx);
    const auto failed = ld.linkInModule(std::move(module.get()));
    sn_assert(!failed, "Failed to link module: " + path.string());
  }
  auto target_machine = get_target_machine();
  optimize(libroot.get().get());
  SNOWBALL_VERBOSE(ctx, "Target triple: " + target_machine->getTargetTriple().str());
  switch (global.emit_type) {
    case EmitType::LlvmBc: {
      std::error_code ec;
      llvm::raw_fd_ostream os(output.string(), ec, llvm::sys::fs::OF_Text);
      sn_assert(!ec, "Failed to open file: " + output.string());
      llvm::WriteBitcodeToFile(*libroot.get(), os);
      os.flush();
      goto exit;
    }
    case EmitType::Llvm: {
      std::error_code ec;
      llvm::raw_fd_ostream os(output.string(), ec, llvm::sys::fs::OF_Text);
      sn_assert(!ec, "Failed to open file: " + output.string());
      auto data_layout = target_machine->createDataLayout();
      libroot.get()->print(os, new CommentWriter(data_layout), false, true);
      os.flush();
      goto exit;
    }
    default: break;
  }
  {
    // Generate object file
    auto obj_output = driver::get_output_path(ctx, ctx.root_package_config.value().project.name + ".tmp");
    output_object_file(*libroot.get(), obj_output, builder_ctx, global.emit_type);
    if (global.emit_type == EmitType::Object) {
      goto exit;
    }
    auto succ = run_linker(ctx, obj_output, output);
    std::filesystem::remove(obj_output);
    if (!succ) {
      return error(F("Linking failed with error code: {}", (int)!succ));
    }
  }
 exit:
  llvm::llvm_shutdown();
  return EXIT_SUCCESS;
}

void LLVMBuilder::output_object_file(llvm::Module& module, std::filesystem::path path,
    std::shared_ptr<llvm::LLVMContext> ctx, EmitType emit_type) {
  auto target_machine = get_target_machine();
  std::error_code ec;
  llvm::raw_fd_ostream os(path.string(), ec, llvm::sys::fs::OF_Text);
  sn_assert(!ec, "Failed to open file: " + path.string());  
  llvm::legacy::PassManager pass;
  auto file_type = llvm::CGFT_ObjectFile;
  if (emit_type == EmitType::Asm) {
    file_type = llvm::CGFT_AssemblyFile;
  }
  module.setDataLayout(target_machine->createDataLayout());
  module.setTargetTriple(target_machine->getTargetTriple().str());
  if (target_machine->addPassesToEmitFile(pass, os, nullptr, file_type)) {
    sn_assert(false, "Target machine can't emit a file of this type");
  }
  pass.run(module);
  os.flush();
}

}
}
