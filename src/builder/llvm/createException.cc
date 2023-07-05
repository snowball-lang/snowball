
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

    auto typeID = builder->getInt32(type->getId());
    auto cast = builder->CreatePointerCast(value, builder->getInt8PtrTy());

    return builder->CreateCall(f, {cast, typeID});
}

} // namespace codegen
} // namespace snowball
