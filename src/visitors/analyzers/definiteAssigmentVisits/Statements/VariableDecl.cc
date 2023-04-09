#include "../../../../ast/errors/error.h"
#include "../../../../errors.h"
#include "../../DefiniteAssigment.h"

#include <utility>

namespace snowball {
namespace Syntax {

SN_DEFINITE_ASSIGMENT_VISIT(Statement::VariableDecl) {
    auto x = p_node->getName();

    if (auto variable = getIdentifier(x)) {
        E<VARIABLE_ERROR>(
            p_node->getDBGInfo(),
            FMT("Variable '%s' has already been defined!", x.c_str()),
            FMT("Defined with the same name at the same scope level.",
                x.c_str()));
    }

    if (p_node->isInitialized()) {
        p_node->getValue()->accept(this);
    }

    this->scopes.front().emplace(std::make_pair(
        x, p_node->isInitialized() ? Initialized : NotInitialized));
}

} // namespace Syntax
} // namespace snowball
