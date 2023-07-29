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
    cast = builder->CreateAlloca(llvmType);
  }
  if (ty->isStruct() || !ty->hasVtable()) return cast;

  // Class specific stuff
  llvm::Value* vtablePointer = nullptr;
  if (auto v = ctx->getVtable(ty->getId())) {
    vtablePointer = v;
  } else {
    auto t = ctx->getVtableTy(ty->getId());
    assert(t != nullptr);

    vtablePointer = createVirtualTable(ty, t);
  }

  auto pointer = builder->CreateInBoundsGEP(llvmType, cast, {builder->getInt32(0), builder->getInt32(0)});
  builder->CreateStore(vtablePointer, pointer);
  return cast;
}

} // namespace codegen
} // namespace snowball
