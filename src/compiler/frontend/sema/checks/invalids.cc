
#include "compiler/frontend/ast/nodes.h"
#include "compiler/frontend/sema/check.h"

namespace snowball {
namespace frontend {
namespace sema {

void TypeChecker::visit(ast::TypeRef* node) { sn_assert(false, "Unreachable typref on typechecker"); }

}
}
}
