
#include "../../ir/values/Call.h"
#include "../../ir/values/Return.h"
#include "../../utils/utils.h"
#include "LLVMBuilder.h"

#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>

namespace snowball {
namespace codegen {

void LLVMBuilder::visit(ir::Return* ret) {

    auto exprValue = ret->getExpr();

    llvm::Value* val = nullptr;
    if (exprValue != nullptr) {
        auto expr = build(exprValue.get());
        val       = builder->CreateRet(expr);
    } else {
        val = builder->CreateRetVoid();
    }

    this->value = val;
}

} // namespace codegen
} // namespace snowball
