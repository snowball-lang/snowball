#include "../../utils/utils.h"
#include "LLVMBuilder.h"

#include <llvm-14/llvm/IR/Type.h>
#include <llvm-14/llvm/IR/Value.h>

namespace snowball {
namespace codegen {

ptr<llvm::Value> LLVMBuilder::allocateObject(std::shared_ptr<types::DefinedType> ty) {
    auto llvmType = getLLVMType(ty);
    auto dataLayout = module->getDataLayout();
    auto allocation = builder->CreateCall(getAllocaFunction(), {builder->getInt32(dataLayout.getTypeAllocSize(llvmType))});
    auto cast = builder->CreatePointerCast(allocation, llvmType);
    return cast;
}


} // namespace codegen
} // namespace snowball
