
#include "../../ir/values/ValueExtract.h"
#include "../../utils/utils.h"
#include "LLVMBuilder.h"

#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>
#include <memory>

namespace snowball {
namespace codegen {

void LLVMBuilder::visit(ir::ValueExtract* extract) {
  auto var = extract->getValue();

  llvm::Value* value = nullptr;
  if (auto f = utils::dyn_cast<ir::Func>(var)) {
    ctx->doNotLoadInMemory = true;
    auto fn = funcs.at(f->getId());
    this->value = fn;
    return;
  } else if (auto v = utils::dyn_cast<ir::Variable>(var)) {
    auto x = ctx->getCurrentIRFunction();
    if (x && v->isUsedInLambda()) {
      llvm::Value* arg = nullptr;
      LLVMBuilderContext::ClosureContext closure;
      if (x->getId() != v->getParentFunc()->getId()) {
        closure = ctx->closures.at(x->getParentScope()->getId());
        int argumentIndex = 0;
        if (utils::is<types::BaseType>(x->getRetTy()))
          argumentIndex++;

        arg = ctx->getCurrentFunction()->getArg(argumentIndex);
      } else {
        closure = ctx->closures.at(x->getId());
        arg = closure.closure;        
      }
      auto index = std::distance(
        closure.variables.begin(),
        std::find_if(
          closure.variables.begin(),
          closure.variables.end(),
          [v](auto v2) { return v2 == v->getId(); }
        )
      );

      value = builder->CreateStructGEP(closure.closureType, arg, index);
    } else {
      // note(argument): "x + 1" because ir::Argument (x - 1) gets
      // created after ir::Variable (x). note(note argument): They are
      // declared as usual with normal ID incrementation
      auto id = v->getId() + v->isArgument();
      value = ctx->getSymbol(id);
    }
  } else {
    assert(false && "BUG: Value extract type not supported!");
  }

  this->value = value;
}

} // namespace codegen
} // namespace snowball
