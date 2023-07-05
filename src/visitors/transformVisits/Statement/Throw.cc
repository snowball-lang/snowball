#include "../../../ir/values/Cast.h"
#include "../../Transformer.h"

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

SN_TRANSFORMER_VISIT(Statement::Raise) {
    p_node->getExpr()->accept(this);
    this->value = builder.createThrow(p_node->getDBGInfo(), this->value);
}

} // namespace Syntax
} // namespace snowball