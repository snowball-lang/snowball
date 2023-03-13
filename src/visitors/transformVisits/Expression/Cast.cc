#include "../../Transformer.h"
#include "../../../ir/values/Cast.h"

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

SN_TRANSFORMER_VISIT(Expression::Cast) {
    p_node->getValue()->accept(this);
    auto t = transformType(p_node->getType());
    auto v = ctx->module->N<ir::Cast>(p_node->getDBGInfo(), this->value, t);
    v->setType(t);
    this->value = v;
}

} // namespace Syntax
} // namespace snowball