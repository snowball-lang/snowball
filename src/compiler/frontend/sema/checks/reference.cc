
#include "compiler/frontend/ast/nodes.h"
#include "compiler/frontend/sema/check.h"

namespace snowball {
namespace frontend {
namespace sema {

void TypeChecker::visit(ast::Reference* node) {
  node->get_expr()->accept(this);
  auto expr_type = node->get_expr()->get_type();
  if (expr_type->is_error()) {
    unify(node->get_type(), ast::types::ErrorType::create());
    return;
  }
  unify(node->get_type(), expr_type->get_reference_to(), node->get_location());
}

}
}
}
