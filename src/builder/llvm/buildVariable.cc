
#include "../../ir/values/Variable.h"
#include "../../utils/utils.h"
#include "LLVMBuilder.h"

#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>

namespace snowball {
namespace codegen {

void LLVMBuilder::visit(ptr<ir::Variable> variable) {
    auto store  = ctx->getSymbol(variable->getId());
    this->value = builder->CreateLoad(getLLVMType(variable->getType()), store);
}

} // namespace codegen
} // namespace snowball
