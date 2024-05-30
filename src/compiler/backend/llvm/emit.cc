
#include "compiler/utils/utils.h"
#include "compiler/utils/logger.h"
#include "compiler/backend/llvm/builder.h"

#include <llvm/Bitcode/BitcodeWriter.h>

namespace snowball {
namespace backend {

int LLVMBuilder::emit(std::filesystem::path path) {
  std::error_code ec;
  llvm::raw_fd_ostream os(path.string(), ec, llvm::sys::fs::OF_None);
  sn_assert(!ec, "Failed to open file: " + path.string());
  llvm::WriteBitcodeToFile(*builder_ctx.module, os);
  os.flush();
  auto file_name = path.filename().stem().string();
  llvm::raw_fd_ostream hos(path.string() + ".hash", ec, llvm::sys::fs::OF_Text);
  sn_assert(!ec, "Failed to open file: " + path.string() + ".hash");
  hos << file_name;
  hos.flush();
  if (vctx.emit_type == EmitType::Llvm) {
    // Replace .bc with .ll
    auto new_path = path;
    new_path.replace_extension(".ll");
    llvm::raw_fd_ostream los(new_path.string(), ec, llvm::sys::fs::OF_Text);
    sn_assert(!ec, "Failed to open file: " + path.string() + ".ll");
    builder_ctx.module->print(los, nullptr);
    los.flush();
  }
  return EXIT_SUCCESS;
}

}
} // namespace snowball
