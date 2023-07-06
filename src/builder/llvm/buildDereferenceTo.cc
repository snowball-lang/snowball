
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

    this->value = builder->CreateLoad(getLLVMType(type), build(val.get()));
}

} // namespace codegen
} // namespace snowball
