
#include "../../../../ast/errors/error.h"
#include "../../../../errors.h"
#include "../../DefiniteAssigment.h"

namespace snowball {
namespace Syntax {

SN_DEFINITE_ASSIGMENT_VISIT(Expression::BinaryOp) {
    if (p_node->op_type == services::OperatorService::EQ) {
        if (auto i = utils::cast<Expression::Identifier>(p_node->left)) {
            if (auto x = getIdentifier(i->getIdentifier())) {
                if (x->second == NotInitialized) {
                    this->scopes.front()[x->first] = Initialized;
                    this->state.inited.push_back(i->getIdentifier());

                    p_node->isInitialization = true;
                }

                return;
            }

            E<VARIABLE_ERROR>(
                p_node->getDBGInfo(),
                FMT("Variable '%s' is used before being assigned.",
                    i->getIdentifier().c_str()),
                FMT("Variable '%s' has been declared but not assigned!",
                    i->getIdentifier().c_str()));
        } else if (auto x = utils::cast<Expression::Index>(p_node->left)) {
            if (auto s = utils::cast<Expression::Identifier>(x->getBase());
                s != nullptr && s->getIdentifier() == "self") {

                if (auto v = getIdentifier(
                        "$self::" + x->getIdentifier()->getIdentifier())) {
                    if (v->second == NotInitialized) {
                        this->scopes.front()[v->first] = Initialized;
                        this->state.inited.push_back(v->first);

                        p_node->isInitialization = true;
                    }
                }
            }
        }
    } else {
        p_node->left->accept(this);
        if (!p_node->unary) {
            p_node->right->accept(this);
        }
    }
}

} // namespace Syntax
} // namespace snowball
