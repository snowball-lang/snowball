
#include "../../DefinitveAssigment.h"

#include <algorithm>
#include <optional>

namespace snowball {
namespace Syntax {

SN_DEFINITE_ASSIGMENT_VISIT(Statement::WhileLoop) {
  p_node->getCondition()->accept(this);
  p_node->getBlock()->accept(this);
}

} // namespace Syntax
} // namespace snowball
