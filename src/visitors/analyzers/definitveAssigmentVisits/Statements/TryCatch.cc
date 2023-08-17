#include "../../DefinitveAssigment.h"

#include <algorithm>
#include <optional>

namespace snowball {
namespace Syntax {

SN_DEFINITE_ASSIGMENT_VISIT(Statement::TryCatch) {
  asBlock([&] {
    for (auto i : p_node->getTryBlock()->getStmts()) { i->accept(this); }
  });
  for (auto& p_node : p_node->getCatchBlocks()) {
    asBlock([&] {
      for (auto i : p_node->getBlock()->getStmts()) { i->accept(this); }
    });
  }
}

} // namespace Syntax
} // namespace snowball
