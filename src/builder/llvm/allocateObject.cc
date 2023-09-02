#include "../../utils/utils.h"
#include "LLVMBuilder.h"

#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>

namespace snowball {
namespace codegen {

llvm::Value* LLVMBuilder::allocateObject(types::DefinedType* ty) {
  auto llvmType = getLLVMType(ty);
  auto llvmTypePtr = getLLVMType(ty)->getPointerTo();
  auto dataLayout = module->getDataLayout();
  llvm::Value* cast = createAlloca(llvmType);
  if (ty->isStruct() || !ty->hasVtable()) return cast;

  // Class specific stuff
  llvm::Value* vtablePointer = nullptr;
  if (auto v = ctx->getVtable(ty->getId())) {
    vtablePointer = v;
  } else {
    auto t = ctx->getVtableTy(ty->getId());
    if (!t) { t = getVtableType(ty); }

    vtablePointer = createVirtualTable(ty, t);
    // insert vtable to the start of the type declaration
    auto body = llvm::cast<llvm::StructType>(llvmType)->elements().vec();
    body[0] = t->getPointerTo();
    llvm::cast<llvm::StructType>(llvmType)->setBody(body);
  }

  auto numElements =
          llvm::cast<llvm::ArrayType>(llvm::cast<llvm::StructType>(ctx->getVtableTy(ty->getId()))->elements()[0])
                  ->getNumElements();
  auto element = llvm::ConstantExpr::getGetElementPtr(
          llvm::StructType::get(llvm::ArrayType::get(builder->getInt8PtrTy(), numElements)),
          (llvm::Constant*)vtablePointer,
          llvm::ArrayRef<llvm::Constant*>{builder->getInt32(0), builder->getInt32(0), builder->getInt32(2)}, true, 1);
  builder->CreateStore(element, cast);
  return cast;
}

} // namespace codegen
} // namespace snowball
