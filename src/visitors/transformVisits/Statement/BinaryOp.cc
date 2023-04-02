#include "../../Transformer.h"

#include <optional>

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

SN_TRANSFORMER_VISIT(Expression::BinaryOp) {
    auto opType = p_node->op_type;
    if (opType == services::OperatorService::EQ) {
        if (auto i = utils::cast<Expression::Identifier>(p_node->left)) {
            auto [v, ty, fns, ovs, mod] = getFromIdentifier(i);

            if (v == std::nullopt && ty == std::nullopt &&
                fns == std::nullopt && ovs == std::nullopt &&
                mod == std::nullopt) {
                E<VARIABLE_ERROR>(p_node,
                                  FMT("Cannot find identifier `%s`!",
                                      i->getIdentifier().c_str()),
                                  "this name is not defined");
            }

            if (v == std::nullopt ||
                (utils::dyn_cast<ir::Variable>(v.value()) == nullptr)) {
                E<SYNTAX_ERROR>(p_node,
                                "You can only assign values to variables!",
                                FMT("Value '%s' is not a variable!",
                                    i->getIdentifier().c_str()));
            }

            auto var = utils::dyn_cast<ir::Variable>(v.value());

            if (!var->isInitialized()) {
                auto variableValue = p_node->right;
                variableValue->accept(this);
                auto varDecl = ctx->module->N<ir::VariableDeclaration>(
                    p_node->getDBGInfo(), var->getIdentifier(), this->value,
                    /* TODO: */ false);
                varDecl->setType(this->value->getType());
                auto itemDecl = std::make_shared<transform::Item>(
                    transform::Item::Type::VALUE, varDecl);

                if (auto f = ctx->getCurrentFunction().get()) {
                    f->addSymbol(varDecl);
                } else {
                    assert(false && "TODO: global variables");
                }

                var->setInitID(varDecl->getId());
                var->setInitialized();
                return;
            }
        } else {
            E<SYNTAX_ERROR>(
                p_node,
                "Can only use identifiers or indexes for variable assigment!");
        }
    }

    assert(false && "TODO: operators");
}

} // namespace Syntax
} // namespace snowball