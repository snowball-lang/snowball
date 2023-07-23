
#include "../../ir/values/Throw.h"
#include "../../utils/utils.h"
#include "LLVMBuilder.h"

#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>
#include <memory>

namespace snowball {
namespace codegen {

void LLVMBuilder::visit(ir::Throw* extract) {
    auto expr = extract->getExpr();
    auto value = build(expr.get());
    auto exception = createException(value, expr->getType());
    auto [type, throwFunction] = getThrowFunction();
    this->value = createCall(type, throwFunction, {exception});
}

} // namespace codegen
} // namespace snowball
