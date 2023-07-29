#include "../../DefinitveAssigment.h"

#include <algorithm>
#include <optional>

namespace snowball {
namespace Syntax {

SN_DEFINITE_ASSIGMENT_VISIT(Statement::TryCatch) {
  p_node->getTryBlock()->accept(this);
  for (auto& p_node : p_node->getCatchBlocks()) { p_node->getBlock()->accept(this); }
}

} // namespace Syntax
} // namespace snowball
