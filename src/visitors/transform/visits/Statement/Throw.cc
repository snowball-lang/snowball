#include "../../../../ir/values/Cast.h"
#include "../../../Transformer.h"

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

SN_TRANSFORMER_VISIT(Statement::Raise) {
    auto expr = trans(p_node->getExpr());
    this->value = builder.createThrow(p_node->getDBGInfo(), expr);
}

} // namespace Syntax
} // namespace snowball