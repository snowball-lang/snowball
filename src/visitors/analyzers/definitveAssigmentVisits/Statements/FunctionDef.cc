
#include "../../../../ast/errors/error.h"
#include "../../../../errors.h"
#include "../../DefinitveAssigment.h"

namespace snowball {
namespace Syntax {

SN_DEFINITE_ASSIGMENT_VISIT(Statement::FunctionDef) {
    if (auto f = utils::cast<Statement::BodiedFunction>(p_node)) {
        bool isConstructor =
                (this->insideClass.has_value() &&
                 services::OperatorService::opEquals<services::OperatorService::CONSTRUCTOR>(
                         p_node->getName()));

        // Scope between parent and body scope for things like "self",
        // arguments, etc...
        withScope([&] {
            if (this->insideClass) {
                this->scopes.front().insert({"self", Initialized});

                if (isConstructor)
                    for (auto x : this->insideClass.value()->getVariables()) {
                        this->scopes.front().insert({"$self::" + x->getName(), NotInitialized});
                    }
            }

            for (auto a : p_node->getArgs()) {
                this->scopes.front().insert({a->getName(), Initialized});
            }

            auto body = f->getBody();
            body->accept(this);

            if (isConstructor) {
                for (auto var : this->scopes.front()) {
                    if (utils::startsWith(var.first, "$self::") && var.second == NotInitialized) {
                        auto name = var.first.substr(7, var.first.size() - 1);
                        // TODO: add highlight of variable from
                        // "insideClass"
                        E<VARIABLE_ERROR>(p_node->getDBGInfo(),
                                          FMT("Class variable '%s' has not "
                                              "been definitivly assigned!",
                                              name.c_str()),
                                          {.info = FMT("The constructor does not define "
                                                       "'self::%s' on all paths.",
                                                       name.c_str())});
                    }
                }
            }
        });
    }
}

} // namespace Syntax
} // namespace snowball
