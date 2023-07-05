
#include "../../utils/utils.h"
#include "LLVMBuilder.h"

#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>

namespace snowball {
namespace codegen {

llvm::Function* LLVMBuilder::getThrowFunction() {
    auto ty = llvm::FunctionType::get(builder->getVoidTy(), {builder->getInt8PtrTy()}, false);
    auto f = llvm::cast<llvm::Function>(module->getOrInsertFunction("sn.eh.throw", ty).getCallee());
    return f;
}

} // namespace codegen
} // namespace snowball
