
#include "../../ir/values/Argument.h"
#include "../../ir/values/VariableDeclaration.h"
#include "../../utils/utils.h"
#include "LLVMBuilder.h"

#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>

namespace snowball {
namespace codegen {

void LLVMBuilder::visit(ir::VariableDeclaration* variable) {
    llvm::Value* store = nullptr;
    if (auto a = utils::cast<ir::Argument>(variable->getValue().get())) {
        auto id = a->getId();
        store = ctx->getSymbol(id);
    } else {
        auto id = variable->getId();
        store = ctx->getSymbol(id);
    }
    auto generatedValue = build(variable->getValue().get());
    auto isPointer = !!utils::dyn_cast<types::ReferenceType>(variable->getType());
    if (generatedValue->getType()->isPointerTy() && !isPointer)
        generatedValue = builder->CreateLoad(generatedValue->getType()->getPointerElementType(),
                                             generatedValue);
    builder->CreateStore(generatedValue, store);
}

} // namespace codegen
} // namespace snowball
