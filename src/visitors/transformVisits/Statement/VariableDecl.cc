#include "../../../ir/values/Cast.h"
#include "../../Transformer.h"

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

SN_TRANSFORMER_VISIT(Statement::VariableDecl) {
    auto definedType   = p_node->getDefinedType() == nullptr
                             ? nullptr
                             : transformType(p_node->getDefinedType());
    auto variableName  = p_node->getName();
    auto variableValue = p_node->getValue();
    auto isMutable     = p_node->isMutable();

    if (ctx->getInScope(variableName, ctx->currentScope()).second) {
        E<VARIABLE_ERROR>(p_node, FMT("Variable with name '%s' is already "
                                      "defined in the current scope!",
                                      variableName.c_str()));
    }

    auto var =
        ctx->module->N<ir::Variable>(p_node->getDBGInfo(), variableName, false);
    auto item =
        std::make_shared<transform::Item>(transform::Item::Type::VALUE, var);

    // TODO: it should always be declared
    if (p_node->isInitialized()) {
        variableValue->accept(this);
        auto varDecl = ctx->module->N<ir::VariableDeclaration>(
            p_node->getDBGInfo(), variableName, this->value, isMutable);
        varDecl->setId(var->getId());
        varDecl->setType(this->value->getType());
        auto itemDecl = std::make_shared<transform::Item>(
            transform::Item::Type::VALUE, varDecl);

        if (auto f = ctx->getCurrentFunction().get()) {
            f->addSymbol(varDecl);
        } else {
            ctx->module->addVariable(varDecl);
        }

        if (definedType == nullptr || definedType->is(this->value->getType())) {
            this->value = varDecl;
        } else {
            if (definedType->canCast(this->value->getType())) {
                auto v      = ctx->module->N<ir::Cast>(p_node->getDBGInfo(),
                                                  this->value, definedType);
                this->value = v;
            } else {
                E<VARIABLE_ERROR>(
                    p_node, FMT("Can't assign value with type '%s' to "
                                "the variable with type '%s'!",
                                this->value->getType()->getPrettyName().c_str(),
                                definedType->getPrettyName().c_str()));
            }
        }

        var->setType(this->value->getType());
    } else {
        auto varDecl = ctx->module->N<ir::VariableDeclaration>(
            p_node->getDBGInfo(), variableName, nullptr, isMutable);
        varDecl->setId(var->getId());
        varDecl->setType(definedType);
        auto itemDecl = std::make_shared<transform::Item>(
            transform::Item::Type::VALUE, varDecl);

        if (auto f = ctx->getCurrentFunction().get()) {
            f->addSymbol(varDecl);
        } else {
            ctx->module->addVariable(varDecl);
        }

        var->setType(definedType);
        this->value = var;
    }

    ctx->addItem(variableName, item);
}

} // namespace Syntax
} // namespace snowball