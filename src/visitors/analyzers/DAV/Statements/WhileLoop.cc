
#include "../../DefinitveAssigment.h"

#include <algorithm>
#include <optional>

namespace snowball {
namespace Syntax {

SN_DEFINITE_ASSIGMENT_VISIT(Statement::WhileLoop) {
  p_node->getCondition()->accept(this);
  asBlock([&] {
          for (auto i : p_node->getBlock()->getStmts()) { i->accept(this); }
          });
}

} // namespace Syntax
} // namespace snowball
