
#include "../../utils/utils.h"
#include "LLVMBuilder.h"

#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>

namespace snowball {
namespace codegen {

llvm::Value* LLVMBuilder::createException(llvm::Value* value, std::shared_ptr<types::Type> type) {
    auto ty = llvm::FunctionType::get(builder->getInt8PtrTy(),
                                      {builder->getInt8PtrTy(), builder->getInt32Ty()}, false);
    auto f =
            llvm::cast<llvm::Function>(module->getOrInsertFunction("sn.eh.create", ty).getCallee());
    f->addRetAttr(llvm::Attribute::NonNull);
    f->addRetAttr(llvm::Attribute::NoAlias);
    f->addRetAttr(llvm::Attribute::NoUndef);
    f->setDoesNotThrow();

    auto usedValue = value;
    if (llvm::isa<llvm::LoadInst>(value)) {
        auto load = llvm::cast<llvm::LoadInst>(value);
        usedValue = load->getOperand(0);
        load->eraseFromParent();
    }

    auto pointerType = utils::dyn_cast<types::ReferenceType>(type);
    auto definedType = utils::dyn_cast<types::DefinedType>(pointerType->getPointedType());
    int typeId = definedType ? definedType->getId() : -1;
    auto cast = builder->CreatePointerCast(usedValue, builder->getInt8PtrTy());

    return builder->CreateCall(f, {cast, builder->getInt32(typeId)});
}

} // namespace codegen
} // namespace snowball
