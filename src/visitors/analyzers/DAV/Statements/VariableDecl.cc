#include "../../../../ast/errors/error.h"
#include "../../../../errors.h"
#include "../../DefinitveAssigment.h"

#include <utility>

namespace snowball {
namespace Syntax {

SN_DEFINITE_ASSIGMENT_VISIT(Statement::VariableDecl) {
  auto x = p_node->getName();

  if (p_node->isInitialized()) { p_node->getValue()->accept(this); }
  auto initialized = p_node->isInitialized() ? Initialized : NotInitialized;
  if (p_node->isExternDecl()) { initialized = Initialized; }
  this->scopes.front().emplace(std::make_pair(x, initialized));
}

} // namespace Syntax
} // namespace snowball
