
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
  return EXIT_SUCCESS;
}

}
} // namespace snowball
