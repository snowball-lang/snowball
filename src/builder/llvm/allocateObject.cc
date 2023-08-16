#include "../../utils/utils.h"
#include "LLVMBuilder.h"

#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>

namespace snowball {
namespace codegen {

llvm::Value* LLVMBuilder::allocateObject(types::DefinedType* ty, bool heapAllocated) {
  auto llvmType = getLLVMType(ty);
  auto llvmTypePtr = getLLVMType(ty)->getPointerTo();
  auto dataLayout = module->getDataLayout();
  llvm::Value* cast = nullptr;
  if (heapAllocated) {
    auto allocation =
            builder->CreateCall(getAllocaFunction(), {builder->getInt32(dataLayout.getTypeAllocSize(llvmType))});
    cast = builder->CreatePointerCast(allocation, llvmTypePtr);
  } else {
    cast = createAlloca(llvmType);
  }
  if (ty->isStruct() || !ty->hasVtable()) return cast;

  // Class specific stuff
  llvm::Value* vtablePointer = nullptr;
  if (auto v = ctx->getVtable(ty->getId())) {
    vtablePointer = v;
  } else {
    auto t = ctx->getVtableTy(ty->getId());
    if (!t) {
      t = getVtableType(ty);
    }
    
    vtablePointer = createVirtualTable(ty, t);
    // insert vtable to the start of the type declaration
    auto body = llvm::cast<llvm::StructType>(llvmType)->elements().vec();
    body[0] = t->getPointerTo();
    llvm::cast<llvm::StructType>(llvmType)->setBody(body);
  }

  auto pointer = builder->CreateConstInBoundsGEP1_32(llvmType, cast, 0);
  builder->CreateStore(vtablePointer, pointer);
  return cast;
}

} // namespace codegen
} // namespace snowball
