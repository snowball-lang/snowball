
#include "../../ir/values/Dereference.h"
#include "../../utils/utils.h"
#include "LLVMBuilder.h"

#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>

namespace snowball {
namespace codegen {

void LLVMBuilder::visit(ir::DereferenceTo* ref) {
  auto val = ref->getValue();
  auto type = ref->getType();

  auto llvmVal = expr(val.get());
  this->value = builder->CreateLoad(getLLVMType(type), llvmVal, ".deref");
  ctx->doNotLoadInMemory = true;
}

} // namespace codegen
} // namespace snowball
