
#include "../../../ast/errors/error.h"
#include "../../../errors.h"
#include "../DefinitveAssigment.h"

namespace snowball {
namespace Syntax {

SN_DEFINITE_ASSIGMENT_VISIT(Macro) {
    withScope([&] {
        for (auto a : p_node->getArgs()) { this->scopes.front().insert({a.first, Initialized}); }
        auto body = p_node->getBody();
        body->accept(this);
    });
}

} // namespace Syntax
} // namespace snowball