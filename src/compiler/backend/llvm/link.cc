
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
  auto engine = llvm::EngineBuilder();
  auto triple_str = libroot.get()->getTargetTriple();
  auto target_machine = engine.selectTarget(llvm::Triple(triple_str), "", "", llvm::SmallVector<std::string, 1>());
  check_and_optimize(libroot.get().get(), target_machine);
  SNOWBALL_VERBOSE(ctx, "Target triple: " + triple_str);
  switch (global.emit_type) {
    case EmitType::LlvmBc: {
      std::error_code ec;
      llvm::raw_fd_ostream os(output.string(), ec, llvm::sys::fs::OF_Text);
      sn_assert(!ec, "Failed to open file: " + output.string());
      llvm::WriteBitcodeToFile(*libroot.get(), os);
      os.flush();
      return EXIT_SUCCESS;
    }
    case EmitType::Llvm: {
      std::error_code ec;
      llvm::raw_fd_ostream os(output.string(), ec, llvm::sys::fs::OF_Text);
      sn_assert(!ec, "Failed to open file: " + output.string());
      libroot.get()->print(os, new CommentWriter(), false, true);
      os.flush();
      return EXIT_SUCCESS;
    }
    default: break;
  }
  // Generate object file
  auto obj_output = driver::get_output_path(ctx, ctx.root_package_config.value().project.name + ".tmp");
  output_object_file(*libroot.get(), obj_output, builder_ctx, target_machine, global.emit_type);
  if (global.emit_type == EmitType::Object) {
    return EXIT_SUCCESS;
  }
  auto succ = run_linker(ctx, obj_output, output, target_machine);
  //std::filesystem::remove(obj_output);
  if (!succ) {
    return error(F("Linking failed with error code: {}", (int)!succ));
  }
  return EXIT_SUCCESS;
}

void LLVMBuilder::output_object_file(llvm::Module& module, std::filesystem::path path,
    std::shared_ptr<llvm::LLVMContext> ctx, llvm::TargetMachine* target_machine, EmitType emit_type) {
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
