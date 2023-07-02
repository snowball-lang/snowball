
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

    auto load = llvm::cast<llvm::LoadInst>(llvmReferencedValue);
    auto value = load->getOperand(0);

    this->value = value;
}

} // namespace codegen
} // namespace snowball
