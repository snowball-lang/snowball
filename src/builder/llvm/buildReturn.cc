
#include "../../ir/values/Call.h"
#include "../../ir/values/Return.h"
#include "../../utils/utils.h"
#include "LLVMBuilder.h"

#include <llvm-14/llvm/IR/Type.h>
#include <llvm-14/llvm/IR/Value.h>

namespace snowball {
namespace codegen {

void LLVMBuilder::visit(ptr<ir::Return> ret) {

    auto exprValue = ret->getExpr();

    ptr<llvm::Value> val = nullptr;
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
