
#include "../../utils/utils.h"
#include "LLVMBuilder.h"

#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>

namespace snowball {
namespace codegen {

llvm::Function* LLVMBuilder::getPrintfFunction() {
  auto ty = llvm::FunctionType::get(builder->getInt32Ty(), {builder->getInt8PtrTy()}, true);
  auto f = llvm::cast<llvm::Function>(module->getOrInsertFunction("printf", ty).getCallee());
  return f;
}

} // namespace codegen
} // namespace snowball
