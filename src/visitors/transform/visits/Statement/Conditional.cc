#include "../../../../ir/values/Conditional.h"

#include "../../../Transformer.h"

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

SN_TRANSFORMER_VISIT(Statement::Conditional) {
  auto expr = getBooleanValue(trans(p_node->getCondition()));
  auto truthyBody = utils::dyn_cast<ir::Block>(trans(p_node->getBlock()));

  std::shared_ptr<ir::Block> falsyBody = nullptr;
  if (auto x = p_node->getElse()) { falsyBody = utils::dyn_cast<ir::Block>(trans(x)); }

  auto cond = builder.createConditional(p_node->getDBGInfo(), expr, truthyBody, falsyBody);
  this->value = utils::dyn_cast<ir::Value>(cond);
}

} // namespace Syntax
} // namespace snowball