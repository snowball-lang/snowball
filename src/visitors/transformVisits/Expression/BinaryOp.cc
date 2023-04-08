#include "../../Transformer.h"

#include <optional>

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

SN_TRANSFORMER_VISIT(Expression::BinaryOp) {
    auto opType = p_node->op_type;
    assert(false && "TODO: operators");
}

} // namespace Syntax
} // namespace snowball