
#include "compiler/frontend/ast/nodes.h"
#include "compiler/frontend/sema/check.h"

namespace snowball {
namespace frontend {
namespace sema {

void TypeChecker::visit(ast::Reference* node) {
  node->get_expr()->accept(this);
  if (auto base = do_deduce(node->get_expr(), true)) {
    auto as_var = base->as<ast::VarDecl>();
    if (!as_var) goto continue_deduce;
    // get_expr->accept takes care if the variable is not initialized
    if (as_var->is_mutably_borrowed()) {
      err(node->get_location(), F("Variable '{}' is already mutably borrowed", as_var->get_name()), Error::Info {
        .highlight = "Borrowed another time here",
        .note = "Cannot borrow a variable mutably more than once"
      }, Error::Type::Err, false);
    } 
    if (node->is_mutable()) {
      as_var->set_mutably_borrowed();
    } else {
      as_var->set_borrowed();
    }
  }
 continue_deduce:
  auto expr_type = node->get_expr()->get_type();
  if (expr_type->is_error()) {
    unify(node->get_type(), get_error_type());
    return;
  }
  unify(node->get_type(), expr_type->get_reference_to(), node->get_location());
}

}
}
}
