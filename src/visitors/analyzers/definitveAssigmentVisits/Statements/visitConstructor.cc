#include "../../../../ast/errors/error.h"
#include "../../../../errors.h"
#include "../../DefinitveAssigment.h"

namespace snowball {
namespace Syntax {

void DefiniteAssigment::visitConstructor(Statement::FunctionDef* p_node) {
    auto constructor = utils::cast<Statement::ConstructorDef>(p_node);
    if (!p_node->isConstructor()) return;

    for (auto superArg : constructor->getSuperArgs()) superArg->accept(this);
    for (auto init : constructor->getInitArgs()) {
        init.second->accept(this);
        auto name = "$self::" + init.first->getIdentifier();
        this->scopes.front()[name] = Initialized;
    }
}

} // namespace Syntax
} // namespace snowball
