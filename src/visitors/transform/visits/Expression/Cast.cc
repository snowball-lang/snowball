#include "../../../../ir/values/Cast.h"

#include "../../../Transformer.h"

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

SN_TRANSFORMER_VISIT(Expression::Cast) {
  auto val = trans(p_node->getValue());
  auto t = transformType(p_node->getType());
  auto v = getBuilder().createCast(p_node->getDBGInfo(), val, t);
  this->value = v;
}

} // namespace Syntax
} // namespace snowball