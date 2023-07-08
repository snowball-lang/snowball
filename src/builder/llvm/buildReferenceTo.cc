
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

    llvm::Value* value = nullptr;
    if (llvm::isa<llvm::LoadInst>(llvmReferencedValue)) {
        // It's already a load instruction, we can just use that
        auto load = llvm::cast<llvm::LoadInst>(llvmReferencedValue);
        value = load->getOperand(0);
    } else {
        // TODO: actually do fix this
        assert(llvmReferencedValue->getType()->isPointerTy());
        value = llvmReferencedValue;
    }

    this->value = value;
}

} // namespace codegen
} // namespace snowball
