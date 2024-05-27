
#include "compiler/ctx.h"
#include "compiler/utils/hash.h"
#include "compiler/backend/drivers.h"
#include "compiler/backend/llvm/builder.h"

#include <llvm/Bitcode/BitcodeWriter.h>

namespace snowball {
namespace backend {

void LLVMBuilder::link(const Ctx& ctx, std::vector<std::filesystem::path>& paths, std::filesystem::path output) {  
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
  check_and_optimize(libroot.get().get(), target_machine, ctx.opt_level);
  SNOWBALL_VERBOSE(ctx, "Target triple: " + triple_str);
  switch (ctx.emit_type) {
    case EmitType::LlvmBc: {
      std::error_code ec;
      llvm::raw_fd_ostream os(output.string(), ec, llvm::sys::fs::OF_Text);
      sn_assert(!ec, "Failed to open file: " + output.string());
      llvm::WriteBitcodeToFile(*libroot.get(), os);
      os.flush();
      return;
    }
    case EmitType::Llvm: {
      std::error_code ec;
      llvm::raw_fd_ostream os(output.string(), ec, llvm::sys::fs::OF_Text);
      sn_assert(!ec, "Failed to open file: " + output.string());
      libroot.get()->print(os, new CommentWriter(), false, true);
      os.flush();
      return;
    }
    default: break;
  }
  // Generate object file
  auto obj_output = driver::get_output_path(ctx, ctx.root_package_config.value().project.name + ".tmp");
  output_object_file(*libroot.get(), obj_output, builder_ctx, target_machine, ctx.emit_type);
  auto cc = driver::get_cc(ctx);
  auto gcc = fmt::format("{}-gcc", triple_str);
  bool is_gcc = false;
  if (cc == "cc" && driver::program_exists(gcc)) {
    cc = gcc;
    is_gcc = true;
  }
  std::vector<std::string> args;
  args.push_back(cc);
  switch (driver::get_linker_type(ctx)) {
    case LinkerType::Lld:
      args.push_back("-fuse-ld=lld");
      break;
    case LinkerType::Mold:
      args.push_back("-fuse-ld=mold");
      break;
    default: break;
  }
  args.push_back("-o");
  args.push_back(output.string());
  args.push_back(obj_output.string());
  if (driver::cc_is_clang(ctx) && !is_gcc) {
    args.push_back("--target=" + triple_str);
  #ifdef SN_LIN
    auto path = fmt::format("/usr/{}", triple_str);
    if (std::filesystem::exists(path)) {
      args.push_back(fmt::format("--sysroot={}", path));
    }
  #endif
  }
  args.push_back("-L");
  args.push_back(driver::get_workspace_path(ctx, driver::WorkSpaceType::Libs).string());
  for (auto& lib : ctx.package_config.value().build.linkage_libs) {
    args.push_back("-l" + lib);
  }
  if (ctx.static_lib) {
    args.push_back("-static");
  }
  if (ctx.emit_type != EmitType::Executable) {
    args.push_back("-flinker-output=dyn");
  }
  args.push_back("-no-pie");
  args.push_back("-lm");
  std::string cmd;
  for (auto& arg : args) {
    cmd += arg + " ";
  }
  SNOWBALL_VERBOSE(ctx, "Using the following command to link: " + cmd);
  std::system(cmd.c_str());
  std::filesystem::remove(obj_output);
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
