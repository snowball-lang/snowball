
#include "compiler/utils/utils.h"
#include "compiler/utils/logger.h"
#include "compiler/backend/llvm/builder.h"

namespace snowball {
namespace backend {

int LLVMBuilder::emit(std::filesystem::path path) {
  std::error_code ec;
  llvm::raw_fd_ostream os(path.string(), ec, llvm::sys::fs::OF_None);
  sn_assert(!ec, "Failed to open file: " + path.string());
  llvm::legacy::PassManager pass;
  auto file_type = llvm::CGFT_AssemblyFile;
  switch (vctx.emit_type) {
    case EmitType::Llvm: {
      llvm::raw_fd_ostream raw_os(path.string(), ec, llvm::sys::fs::OF_None);
      dump(raw_os);
      utils::Logger::info("Snowball project compiled to an LLVM file! ✨\n");
      return EXIT_SUCCESS;
    }
    case EmitType::Object:
      file_type = llvm::CGFT_ObjectFile;
      break;
    case EmitType::Executable:
      file_type = llvm::CGFT_ObjectFile;
      break;
    case EmitType::Asm:
      file_type = llvm::CGFT_AssemblyFile;
      break;
    default: sn_unreachable();
  }
  if (builder_ctx.target_machine->addPassesToEmitFile(pass, os, nullptr, file_type)) {
    sn_assert(false, "The target machine can't emit a file of this type");
  }
  utils::Logger::info("Snowball project compiled to an object file! ✨\n");
  pass.run(*builder_ctx.module);
  os.flush();
  return EXIT_SUCCESS;
}

}
} // namespace snowball
