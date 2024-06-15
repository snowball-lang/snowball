
#include "compiler/frontend/ast/nodes.h"
#include "compiler/frontend/sema/check.h"

namespace snowball {
namespace frontend {
namespace sema {

void TypeChecker::visit(ast::Dereference* node) {
  auto expr = node->get_expr();
  expr->accept(this);
  auto expr_type = expr->get_type();
  if (expr_type->is_error()) {
    unify(node->get_type(), get_error_type());
    return;
  }
  if (!expr_type->is_pointer() && !expr_type->is_reference()) {
    err(node->get_location(), "dereferencing non-pointer expression", Error::Info {
      .highlight = "Expected a pointer type",
      .help = "Did you mean to dereference a pointer?"
    }, Error::Type::Err, false);
    unify(node->get_type(), get_error_type());
    return;
  }
  auto pointee_type = expr_type->is_pointer() 
    ? expr_type->as_pointer()->get_pointee() 
    : expr_type->as_reference()->get_ref();
  unify(node->get_type(), pointee_type, node->get_location());
}

}
}
}
