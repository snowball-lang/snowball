
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
                }

                return;
            }

            E<VARIABLE_ERROR>(
                p_node->getDBGInfo(),
                FMT("Variable '%s' is used before being assigned.",
                    i->getIdentifier().c_str()),
                FMT("Variable '%s' has been declared but not assigned!",
                    i->getIdentifier().c_str()));
        }
    }
}

} // namespace Syntax
} // namespace snowball
