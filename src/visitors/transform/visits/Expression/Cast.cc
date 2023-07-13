#include "../../../../ir/values/Cast.h"

#include "../../../Transformer.h"

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

SN_TRANSFORMER_VISIT(Expression::Cast) {
    p_node->getValue()->accept(this);
    auto t = transformType(p_node->getType());
    auto v = builder.createCast(p_node->getDBGInfo(), this->value, t);
    this->value = v;
}

} // namespace Syntax
} // namespace snowball