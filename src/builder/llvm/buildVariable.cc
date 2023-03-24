
#include "../../ir/values/Variable.h"
#include "../../utils/utils.h"
#include "LLVMBuilder.h"

#include <llvm-14/llvm/IR/Type.h>
#include <llvm-14/llvm/IR/Value.h>

namespace snowball {
namespace codegen {

void LLVMBuilder::visit(ptr<ir::Variable> variable) {
    // note: "x - 1" because ir::Variable (x + 1) gets created after VariableDeclaration (x).
    auto store = ctx->getSymbol(variable->getId() - 1);
    this->value = builder->CreateLoad(getLLVMType(variable->getType()), store);
}

} // namespace codegen
} // namespace snowball
