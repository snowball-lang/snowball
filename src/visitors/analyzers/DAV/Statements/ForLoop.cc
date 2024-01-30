
#include "../../DefinitveAssigment.h"

#include <algorithm>
#include <optional>

namespace snowball {
namespace Syntax {

SN_DEFINITE_ASSIGMENT_VISIT(Statement::ForLoop) {
  // TODO: add iterator variable
  p_node->getExpr()->accept(this);
  asBlock([&] {
            for (auto i : p_node->getBlock()->getStmts()) { i->accept(this); }
          });
}

} // namespace Syntax
} // namespace snowball
