
#include "../../ir/values/ReferenceTo.h"
#include "../../utils/utils.h"
#include "LLVMBuilder.h"

#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>

namespace snowball {
namespace codegen {

void LLVMBuilder::visit(ir::ReferenceTo* ref) {
  auto val = ref->getValue();
  auto llvmReferencedValue = build(val.get());

  //if (!llvmReferencedValue->getType()->isPointerTy() || ctx->doNotLoadInMemory) {
  //  auto tempVal = createAlloca(getLLVMType(val->getType()));
  //  builder->CreateStore(llvmReferencedValue, tempVal);
  //  llvmReferencedValue = tempVal;
  //}

  //if (llvm::isa<llvm::LoadInst>(llvmReferencedValue)) {
  //  llvmReferencedValue = llvm::cast<llvm::LoadInst>(llvmReferencedValue)->getPointerOperand();
  //}

  //builder->CreateStore(llvmReferencedValue, tempVal);
  auto tempVal = (llvm::Value*)nullptr;
  if (llvm::isa<llvm::Constant>(llvmReferencedValue)) {
    tempVal = createAlloca(llvmReferencedValue->getType(), ".ref-temp");
    builder->CreateStore(llvmReferencedValue, tempVal);
  } else {
    tempVal = llvmReferencedValue;
  }

  ctx->doNotLoadInMemory = true;
  this->value = tempVal;
}

} // namespace codegen
} // namespace snowball
