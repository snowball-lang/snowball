#include "../../../ir/values/Conditional.h"

#include "../../Transformer.h"

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

SN_TRANSFORMER_VISIT(Statement::Conditional) {
    p_node->getCondition()->accept(this);
    auto expr = getBooleanValue(this->value);

    p_node->getBlock()->accept(this);
    auto truthyBody = utils::dyn_cast<ir::Block>(this->value);

    std::shared_ptr<ir::Block> falsyBody = nullptr;
    if (auto x = p_node->getElse()) {
        x->accept(this);
        falsyBody = utils::dyn_cast<ir::Block>(this->value);
    }

    auto cond = ctx->module->N<ir::Conditional>(p_node->getDBGInfo(), expr, truthyBody, falsyBody);
    this->value = utils::dyn_cast<ir::Value>(cond);
}

} // namespace Syntax
} // namespace snowball