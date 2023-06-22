
#include "../DefinitveAssigment.h"

namespace snowball {
namespace Syntax {

SN_DEFINITE_ASSIGMENT_VISIT(Statement::Return) {
    if (auto x = p_node->getValue()) { x->accept(this); }
}

SN_DEFINITE_ASSIGMENT_VISIT(Expression::NewInstance) {
    for (auto a : p_node->getCall()->getArguments()) { a->accept(this); }
}

SN_DEFINITE_ASSIGMENT_VISIT(Expression::Cast) { p_node->getValue()->accept(this); }

SN_DEFINITE_ASSIGMENT_VISIT(Expression::GenericIdentifier) {
    utils::cast<Expression::Identifier>(p_node)->accept(this);
}

SN_DEFINITE_ASSIGMENT_VISIT(Expression::FunctionCall) {
    for (auto a : p_node->getArguments()) { a->accept(this); }
}

SN_DEFINITE_ASSIGMENT_VISIT(Statement::ClassDef) {
    auto bk = this->insideClass;
    this->insideClass = p_node;
    for (auto fn : p_node->getFunctions()) { fn->accept(this); }
    this->insideClass = bk;
}

} // namespace Syntax
} // namespace snowball
