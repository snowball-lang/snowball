#include "../../utils/utils.h"
#include "LLVMBuilder.h"

#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>

namespace snowball {
namespace codegen {

llvm::Value *
LLVMBuilder::allocateObject(std::shared_ptr<types::DefinedType> ty) {
    auto llvmType   = getLLVMType(ty);
    auto dataLayout = module->getDataLayout();
    auto allocation = builder->CreateCall(
        getAllocaFunction(),
        {builder->getInt32(dataLayout.getTypeAllocSize(llvmType))});
    auto cast = builder->CreatePointerCast(allocation, llvmType);

    llvm::Value *vtablePointer = nullptr;
    if (auto v = ctx->getVtable(ty->getId())) {
        vtablePointer = v;
    } else {
        auto t = ctx->getVtableTy(ty->getId());
        assert(t != nullptr);

        vtablePointer = createVirtualTable(ty.get(), t);
    }

    auto pointer = builder->CreateInBoundsGEP(
        llvmType->getPointerElementType(), cast,
        {builder->getInt32(0), builder->getInt32(0)});
    builder->CreateStore(vtablePointer, pointer);

    return cast;
}

} // namespace codegen
} // namespace snowball
