
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

  if (!llvmReferencedValue->getType()->isPointerTy() || ctx->doNotLoadInMemory) {
    auto tempVal = createAlloca(getLLVMType(val->getType()));
    builder->CreateStore(llvmReferencedValue, tempVal);
    llvmReferencedValue = tempVal;
  }

  auto tempVal = createAlloca(getLLVMType(ref->getType()));
  builder->CreateStore(llvmReferencedValue, tempVal);
  ctx->doNotLoadInMemory = false;

  this->value = tempVal;
}

} // namespace codegen
} // namespace snowball
