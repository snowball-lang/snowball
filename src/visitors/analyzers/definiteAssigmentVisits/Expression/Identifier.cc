
#include "../../../../ast/errors/error.h"
#include "../../../../errors.h"
#include "../../DefiniteAssigment.h"

namespace snowball {
namespace Syntax {

SN_DEFINITE_ASSIGMENT_VISIT(Expression::Identifier) {
    auto x = p_node->getIdentifier();

    if (auto variable = getIdentifier(x)) {
        if (variable->second == NotInitialized) {
            E<VARIABLE_ERROR>(
                p_node->getDBGInfo(),
                FMT("Variable '%s' is used before being assigned.", x.c_str()),
                FMT("Variable '%s' has been declared but not assigned!",
                    x.c_str()));
        }

        return;
    }

    // E<VARIABLE_ERROR>(p_node->getDBGInfo(),
    //                   FMT("Cannot find identifier `%s`!", x.c_str()),
    //                   "this name is not defined");
}

} // namespace Syntax
} // namespace snowball
