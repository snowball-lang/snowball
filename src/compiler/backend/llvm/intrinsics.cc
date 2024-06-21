
#include "compiler/backend/llvm/builder.h"

namespace snowball {
namespace backend {

void LLVMBuilder::create_memcopy(llvm::Value* dst, llvm::Value* src, uint64_t size) {
  builder->CreateMemCpy(dst, llvm::MaybeAlign(1), src, llvm::MaybeAlign(1), size);
}

void LLVMBuilder::create_memset(llvm::Value* dst, llvm::Value* value, uint64_t size) {
  builder->CreateMemSet(dst, value, size, llvm::MaybeAlign(1));
}

}
} // namespace snowball
