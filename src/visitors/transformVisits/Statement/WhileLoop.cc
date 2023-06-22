#include "../../../ir/values/WhileLoop.h"

#include "../../Transformer.h"

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball
{
namespace Syntax
{

SN_TRANSFORMER_VISIT(Statement::WhileLoop) {
    p_node->getCondition()->accept(this);
    auto expr = getBooleanValue(this->value);

    p_node->getBlock()->accept(this);
    auto body = utils::dyn_cast<ir::Block>(this->value);

    auto cond =
            ctx->module->N<ir::WhileLoop>(p_node->getDBGInfo(), expr, body, p_node->isDoWhile());
    this->value = utils::dyn_cast<ir::Value>(cond);
}

} // namespace Syntax
} // namespace snowball