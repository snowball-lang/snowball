
#include <cassert>

#include "compiler/frontend/ast/nodes.h"
#include "compiler/frontend/sema/check.h"

namespace snowball {
namespace frontend {
namespace sema {

bool TypeChecker::unify(ast::types::Type*& a, ast::types::Type* b) {
  if (!a) return (a = b);
  assert(false && "unimplemented");
  return false;
}

}
}
}
