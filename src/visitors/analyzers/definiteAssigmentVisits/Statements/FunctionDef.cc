
#include "../../DefiniteAssigment.h"

namespace snowball {
namespace Syntax {

SN_DEFINITE_ASSIGMENT_VISIT(Statement::FunctionDef) {
    if (auto f = utils::cast<Statement::BodiedFunction>(p_node)) {
        auto body = f->getBody();
        body->accept(this);
    }
}

} // namespace Syntax
} // namespace snowball
