
#include "compiler/frontend/ast/nodes.h"
#include "compiler/frontend/sema/check.h"

namespace snowball {
namespace frontend {
namespace sema {

void TypeChecker::visit(ast::Block* node) {
  for (auto& stmt : node->get_stmts()) {
    stmt->accept(this);
  }
}

}
}
}
