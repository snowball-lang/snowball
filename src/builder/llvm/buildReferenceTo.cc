
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

  auto tempVal = (llvm::Value*)createAlloca(getLLVMType(ref->getType()), ".ref-temp");
  builder->CreateStore(llvmReferencedValue, tempVal);
  //builder->CreateMemCpy(tempVal, llvm::MaybeAlign(), llvmReferencedValue, llvm::MaybeAlign(), ref->getType()->sizeOf(), false);
  ctx->doNotLoadInMemory = false;

  this->value = tempVal;
}

} // namespace codegen
} // namespace snowball
