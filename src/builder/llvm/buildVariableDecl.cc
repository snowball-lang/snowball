
#include "../../ir/values/Argument.h"
#include "../../ir/values/VariableDeclaration.h"
#include "../../utils/utils.h"
#include "LLVMBuilder.h"

#include <llvm-14/llvm/IR/Type.h>
#include <llvm-14/llvm/IR/Value.h>

namespace snowball {
namespace codegen {

void LLVMBuilder::visit(ptr<ir::VariableDeclaration> variable) {
    ptr<llvm::Value> store = nullptr;

    if (auto a = utils::cast<ir::Argument>(variable->getValue().get())) {
        auto id = a->getId();
        store   = ctx->getSymbol(id);
    } else {
        auto id = variable->getId();
        store   = ctx->getSymbol(id);
    }

    auto generatedValue = build(variable->getValue().get());
    builder->CreateStore(generatedValue, store);
}

} // namespace codegen
} // namespace snowball
