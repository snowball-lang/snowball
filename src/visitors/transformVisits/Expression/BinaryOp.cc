#include "../../Transformer.h"

#include <optional>

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

SN_TRANSFORMER_VISIT(Expression::BinaryOp) {
    auto opType = p_node->op_type;

    if (p_node->unary) {
        if (opType == Expression::BinaryOp::OpType::REFERENCE) {
            p_node->left->accept(this);
            auto value = this->value;
            auto ref = builder.createReferenceTo(p_node->getDBGInfo(), value);
            this->value = ref;
            return;
        } else if (opType == Expression::BinaryOp::OpType::DEREFERENCE) {
            p_node->left->accept(this);
            auto value = this->value;
            auto type = value->getType();
            if (auto x = utils::dyn_cast<types::ReferenceType>(type)) {
                type = x->getBaseType();
            } else {
                E<DEREFERENCE_ERROR>(p_node, "Can't dereference a non-pointer type!");
            }

            auto ref = builder.createDereferenceTo(p_node->getDBGInfo(), value, type);
            this->value = ref;
            return;
        }

        assert(false && "TODO:");
    }

    auto left = p_node->left;
    auto right = p_node->right;

    auto ident =
            Syntax::N<Expression::Identifier>(services::OperatorService::getOperatorMangle(opType));
    auto index = Syntax::N<Expression::Index>(left, ident);
    std::vector<Expression::Base*> args = {right};
    auto call = Syntax::N<Expression::FunctionCall>(index, args);

    call->isInitialization = p_node->isInitialization;

    ident->setDBGInfo(p_node->getDBGInfo());
    call->setDBGInfo(p_node->getDBGInfo());
    index->setDBGInfo(p_node->getDBGInfo());

    call->accept(this);
    auto assigmentAsCall = utils::dyn_cast<ir::Call>(this->value);
    auto assigmentValue = builder.createBinaryOp(assigmentAsCall);
    this->value = assigmentValue;
}

} // namespace Syntax
} // namespace snowball