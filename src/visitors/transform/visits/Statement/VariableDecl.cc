#include "../../../../ir/values/Cast.h"
#include "../../../Transformer.h"

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

SN_TRANSFORMER_VISIT(Statement::VariableDecl) {
    auto definedType =
            p_node->getDefinedType() == nullptr ? nullptr : transformType(p_node->getDefinedType());
    auto variableName = p_node->getName();
    auto variableValue = p_node->getValue();
    auto isMutable = p_node->isMutable();
    assert(p_node->isInitialized() || definedType != nullptr);
    if (ctx->getInScope(variableName, ctx->currentScope()).second) {
        E<VARIABLE_ERROR>(p_node,
                          FMT("Variable with name '%s' is already "
                              "defined in the current scope!",
                              variableName.c_str()));
    }

    auto var = builder.createVariable(p_node->getDBGInfo(), variableName, false, isMutable);
    auto item = std::make_shared<transform::Item>(transform::Item::Type::VALUE, var);
    // TODO: it should always be declared
    if (p_node->isInitialized()) {
        auto val = trans(variableValue);
        auto varDecl = builder.createVariableDeclaration(
                p_node->getDBGInfo(), variableName, val, isMutable);
        varDecl->setId(var->getId());
        varDecl->setType(val->getType());
        auto itemDecl = std::make_shared<transform::Item>(transform::Item::Type::VALUE, varDecl);

        if (auto f = ctx->getCurrentFunction().get()) {
            f->addSymbol(varDecl);
        } else {
            ctx->module->addVariable(varDecl);
        }

        if (definedType == nullptr || definedType->is(val->getType())) {
            this->value = varDecl;
        } else {
            if (definedType->canCast(val->getType())) {
                auto v = builder.createCast(p_node->getDBGInfo(), val, definedType);
                this->value = v;
            } else {
                E<VARIABLE_ERROR>(p_node,
                                  FMT("Can't assign value with type '%s' to "
                                      "the variable with type '%s'!",
                                      val->getType()->getPrettyName().c_str(),
                                      definedType->getPrettyName().c_str()));
            }
        }

        var->setType(val->getType());
    } else {
        auto varDecl = builder.createVariableDeclaration(
                p_node->getDBGInfo(), variableName, nullptr, isMutable);
        varDecl->setId(var->getId());
        varDecl->setType(definedType);
        auto itemDecl = std::make_shared<transform::Item>(transform::Item::Type::VALUE, varDecl);

        if (auto f = ctx->getCurrentFunction().get()) {
            f->addSymbol(varDecl);
        } else {
            ctx->module->addVariable(varDecl);
        }

        var->setType(definedType);
        this->value = var;
    }

    auto type = this->value->getType();
    if (isMutable != type->isMutable()) { type->setMutable(isMutable); }

    ctx->addItem(variableName, item);
}

} // namespace Syntax
} // namespace snowball