
#include "compiler/frontend/ast/nodes.h"
#include "compiler/frontend/sema/check.h"

namespace snowball {
namespace frontend {
namespace sema {

void TypeChecker::visit(ast::MemberAccess* node) {
  sn_assert(false, "MemberAccess not implemented");
}

}
}
}

