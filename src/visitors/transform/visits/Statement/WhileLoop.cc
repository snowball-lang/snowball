#include "../../../../ir/values/WhileLoop.h"

#include "../../../Transformer.h"

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

SN_TRANSFORMER_VISIT(Statement::WhileLoop) {
    auto cond = trans(p_node->getCondition());
    auto expr = getBooleanValue(cond);

    auto block = trans(p_node->getBlock());
    auto body = utils::dyn_cast<ir::Block>(block);

    auto loop = builder.createWhileLoop(p_node->getDBGInfo(), expr, body, p_node->isDoWhile());
    this->value = utils::dyn_cast<ir::Value>(loop);
}

} // namespace Syntax
} // namespace snowball