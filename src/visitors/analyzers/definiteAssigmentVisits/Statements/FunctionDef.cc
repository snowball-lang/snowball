
#include "../../DefiniteAssigment.h"

namespace snowball {
namespace Syntax {

SN_DEFINITE_ASSIGMENT_VISIT(Statement::FunctionDef) {
    if (auto f = utils::cast<Statement::BodiedFunction>(p_node)) {
        // Scope between parent and body scope for things like "self", arguments, etc...
        withScope([&] {
            if (this->insideClass) {
                this->scopes.front().insert({"self", Initialized});
            }

            for (auto a : p_node->getArgs()) {
                this->scopes.front().insert({a->getName(), Initialized});
            }

            auto body = f->getBody();
            body->accept(this);
        });
    }
}

} // namespace Syntax
} // namespace snowball
