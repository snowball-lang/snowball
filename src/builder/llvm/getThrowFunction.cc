
#include "../../utils/utils.h"
#include "LLVMBuilder.h"

#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>

namespace snowball {
namespace codegen {

std::pair<llvm::FunctionType*, llvm::Function*> LLVMBuilder::getThrowFunction() {
  auto ty = llvm::FunctionType::get(builder->getVoidTy(), {builder->getInt8PtrTy()}, false);
  auto f = llvm::cast<llvm::Function>(module->getOrInsertFunction(getSharedLibraryName("sn.eh.throw"), ty).getCallee());
  return {ty, f};
}

} // namespace codegen
} // namespace snowball
