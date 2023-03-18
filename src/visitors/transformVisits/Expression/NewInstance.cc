#include "../../Transformer.h"
#include "../../../services/OperatorService.h"

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

SN_TRANSFORMER_VISIT(Expression::NewInstance) {
    auto call = p_node->getCall();
    auto expr = call->getCallee();

    assert(utils::cast<Expression::TypeRef>(expr));
    auto ident = Syntax::N<Expression::Identifier>(services::OperatorService::getOperatorMangle(services::OperatorService::CONSTRUCTOR));
    auto index = Syntax::N<Expression::Index>(expr, ident, true);

    ident->setDBGInfo(expr->getDBGInfo());
    index->setDBGInfo(expr->getDBGInfo());

    call->setCallee(index);
    call->accept(this);
}

} // namespace Syntax
} // namespace snowball