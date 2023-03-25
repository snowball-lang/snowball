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

    assert(definedType == nullptr && "TODO: cast for desired type");
    if (ctx->getInScope(variableName, ctx->currentScope()).second) {
        E<VARIABLE_ERROR>(p_node, FMT("Variable with name '%s' is already "
                                      "defined in the current scope!",
                                      variableName.c_str()));
    }

    variableValue->accept(this);
    auto varDecl = ctx->module->N<ir::VariableDeclaration>(p_node->getDBGInfo(), variableName,
                                            this->value, isMutable);
    varDecl->setType(this->value->getType());
    auto itemDecl =
        std::make_shared<transform::Item>(transform::Item::Type::VALUE, varDecl);

    auto var = ctx->module->N<ir::Variable>(p_node->getDBGInfo(), variableName);
    var->setType(this->value->getType());
    auto item =
        std::make_shared<transform::Item>(transform::Item::Type::VALUE, var);

    ctx->addItem(variableName, item);
    var->setType(varDecl->getType());
    var->setId(varDecl->getId());

    if (auto f = ctx->getCurrentFunction().get()) {
        f->addSymbol(varDecl);
    } else {
        assert(false && "TODO: global variables");
    }

    this->value = var;
}

} // namespace Syntax
} // namespace snowball