#include "../../Transformer.h"

#include <optional>

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

SN_TRANSFORMER_VISIT(Expression::BinaryOp) {
    auto opType = p_node->op_type;
    assert(false && "TODO:");

    if (p_node->unary) {
        assert(false && "TODO:");
    }

    auto left  = p_node->left;
    auto right = p_node->right;

    auto ident = Syntax::N<Expression::Identifier>(
        services::OperatorService::getOperatorMangle(opType));
    auto index = Syntax::N<Expression::Index>(left, ident, false);
    std::vector<Expression::Base *> args = {right};
    auto call = Syntax::N<Expression::FunctionCall>(index, args);

    ident->setDBGInfo(p_node->getDBGInfo());
    call->setDBGInfo(p_node->getDBGInfo());
    index->setDBGInfo(p_node->getDBGInfo());

    call->accept(this);
}

} // namespace Syntax
} // namespace snowball