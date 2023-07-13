#include "../../../Transformer.h"

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

SN_TRANSFORMER_VISIT(Statement::Return) {
    auto functionType = utils::dyn_cast<types::FunctionType>(ctx->getCurrentFunction()->getType());
    assert(functionType);
    if (auto f = ctx->getCurrentFunction(); f->isConstructor()) {
        E<SYNTAX_ERROR>(p_node,
                        "You can't return a value inside a constructor function!",
                        {.info = "Constructors can't contain return statements"});
    }

    std::shared_ptr<ir::Value> ret = nullptr;
    if (!utils::dyn_cast<types::VoidType>(functionType->getRetType())) {
        std::shared_ptr<ir::Value> returnValue = nullptr;
        if (p_node->getValue() != nullptr) {
            returnValue = trans(p_node->getValue());
        } else {
            E<SYNTAX_ERROR>(p_node,
                            "You must return a value inside a non-void function!",
                            {.info = "Non-void functions must contain return statements"});
        }

        ret = builder.createReturn(p_node->getDBGInfo(), returnValue);
    } else {
        if (p_node->getValue() != nullptr) {
            E<SYNTAX_ERROR>(p_node,
                            "You can't return a value inside a void function!",
                            {.info = "Void functions can't contain return statements"});
        }

        ret = builder.createVoidReturn(p_node->getDBGInfo());
    }
    this->value = ret;
}

} // namespace Syntax
} // namespace snowball