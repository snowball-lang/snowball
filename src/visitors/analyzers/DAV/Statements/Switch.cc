#include "../../DefinitveAssigment.h"

#include <algorithm>
#include <optional>

namespace snowball {
namespace Syntax {

SN_DEFINITE_ASSIGMENT_VISIT(Statement::Switch) {
  p_node->getExpr()->accept(this);
  for (auto& caseInstance : p_node->getCases()) {
    asBlock([&] {
            for (auto i : caseInstance.block->getStmts()) { i->accept(this); }
            });
  }
}

} // namespace Syntax
} // namespace snowball
