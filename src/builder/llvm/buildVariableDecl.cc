
#include "../../ir/values/Argument.h"
#include "../../ir/values/VariableDeclaration.h"
#include "../../ir/values/Call.h"
#include "../../utils/utils.h"
#include "LLVMBuilder.h"

#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>

namespace snowball {
namespace codegen {

void LLVMBuilder::visit(ir::VariableDeclaration* variable) {
  llvm::Value* store = nullptr;
  ctx->doNotLoadInMemory = false;
  if (auto a = utils::cast<ir::Argument>(variable->getValue().get())) {
    auto id = a->getId();
    store = ctx->getSymbol(id);
  } else {
    auto id = variable->getId();
    store = ctx->getSymbol(id);
  }
  if (utils::is<ir::Call>(variable->getValue().get()) && utils::is<types::DefinedType>(variable->getType())) {
    ctx->callStoreValue = store;
    build(variable->getValue().get());
    ctx->callStoreValue = nullptr;
  } else {
    auto generatedValue = expr(variable->getValue().get());
    builder->CreateStore(generatedValue, store);
  }
}

} // namespace codegen
} // namespace snowball
