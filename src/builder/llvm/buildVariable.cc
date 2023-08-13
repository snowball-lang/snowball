
#include "../../ir/values/Variable.h"
#include "../../utils/utils.h"
#include "LLVMBuilder.h"

#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>

namespace snowball {
namespace codegen {

void LLVMBuilder::visit(ir::Variable* variable) {
  auto store = ctx->getSymbol(variable->getId() + variable->isArgument());
  if (utils::cast<types::DefinedType>(variable->getType())) { // not a pointer
    this->value = store;
    return;
  }
  auto type = variable->getType();
  this->value = builder->CreateLoad(getLLVMType(type), store, ".ve");
}

} // namespace codegen
} // namespace snowball
