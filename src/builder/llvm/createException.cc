
#include "../../utils/utils.h"
#include "LLVMBuilder.h"

#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>

namespace snowball {
namespace codegen {

llvm::Value* LLVMBuilder::createException(llvm::Value* value, types::Type* type) {
  auto ty = llvm::FunctionType::get(builder->getInt8PtrTy(), {builder->getInt8PtrTy(), builder->getInt32Ty()}, false);
  auto f =
  llvm::cast<llvm::Function>(module->getOrInsertFunction(getSharedLibraryName("sn.eh.create"), ty).getCallee());
  f->addRetAttr(llvm::Attribute::NonNull);
  f->addRetAttr(llvm::Attribute::NoAlias);
  f->addRetAttr(llvm::Attribute::NoUndef);
  f->setDoesNotThrow();
  auto usedValue = value; // use LLVMBuilder::load instead?
  int typeId = typeIdxLookup(type->getMangledName());
  auto cast = builder->CreatePointerCast(usedValue, builder->getInt8PtrTy());
  return builder->CreateCall(f, {cast, builder->getInt32(typeId)});
}

} // namespace codegen
} // namespace snowball
