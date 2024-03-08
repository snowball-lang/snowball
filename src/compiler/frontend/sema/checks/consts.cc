
#include "compiler/frontend/ast/nodes.h"
#include "compiler/frontend/sema/check.h"

namespace snowball {
namespace frontend {
namespace sema {

void TypeChecker::visit(ast::Number* node) {
    unify(node->get_type(), get_type("i32"), node->get_location());
}

}
}
}
