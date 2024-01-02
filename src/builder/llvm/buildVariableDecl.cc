
#include "../../ir/values/Argument.h"
#include "../../ir/values/EnumInit.h"
#include "../../ir/values/Call.h"
#include "../../ir/values/VariableDeclaration.h"
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
    if (variable->getVariable()->isUsedInLambda()) {
      auto closure = ctx->closures.at(ctx->getCurrentIRFunction()->getId());

      auto index = std::distance(
        closure.variables.begin(),
        std::find_if(
          closure.variables.begin(),
          closure.variables.end(),
          [variable](auto& v) { return v == variable->getVariable()->getId(); }
        )
      );

      store = builder->CreateStructGEP(closure.closureType, closure.closure, index);
    } else {
      auto id = variable->getId();
      store = ctx->getSymbol(id);
    }
  }

  // debug info
  if (auto llvmFn = ctx->getCurrentFunction()) {
    auto dbgInfo = variable->getDBGInfo();
    auto src = variable->getSourceInfo();
    auto file = dbg.getFile(src->getPath());
    auto scope = llvmFn->getSubprogram();
    auto debugVar = dbg.builder->createAutoVariable(
            scope, variable->getIdentifier(), file, dbgInfo->line, getDIType(variable->getType()), dbg.debug
    );
    dbg.builder->insertDeclare(
            store,
            debugVar,
            dbg.builder->createExpression(),
            llvm::DILocation::get(*context, dbgInfo->line, dbgInfo->pos.second, scope),
            builder->GetInsertBlock()
    );
  }

  if (utils::is<ir::Call>(variable->getValue().get()) && !utils::is<ir::EnumInit>(utils::dyn_cast<ir::Call>(variable->getValue())->getCallee().get()) && utils::is<types::BaseType>(variable->getType())) {
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
