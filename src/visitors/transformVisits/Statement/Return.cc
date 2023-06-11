#include "../../Transformer.h"

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

SN_TRANSFORMER_VISIT(Statement::Return) {

    if (auto f = ctx->getCurrentFunction(); f->isConstructor()) {
        E<SYNTAX_ERROR>(
            p_node, "You can't return a value inside a constructor function!",
            {.info = "Constructors can't contain return statements"});
    }

    std::shared_ptr<ir::Value> returnValue = nullptr;
    if (p_node->getValue() != nullptr) {
        p_node->getValue()->accept(this);

        returnValue = this->value;
    }

    auto ret = ctx->module->N<ir::Return>(p_node->getDBGInfo(), returnValue);

    // We shoudn't do this since return statements can't be use as
    // values. We do this just in case we need it for some convinience
    ret->setType(returnValue->getType());

    this->value = ret;
}

} // namespace Syntax
} // namespace snowball