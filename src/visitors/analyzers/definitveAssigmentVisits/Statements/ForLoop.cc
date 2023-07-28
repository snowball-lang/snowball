
#include "../../DefinitveAssigment.h"

#include <algorithm>
#include <optional>

namespace snowball {
namespace Syntax {

SN_DEFINITE_ASSIGMENT_VISIT(Statement::ForLoop) {
    // TODO: add iterator variable
    p_node->getExpr()->accept(this);
    p_node->getBlock()->accept(this);
}

} // namespace Syntax
} // namespace snowball
