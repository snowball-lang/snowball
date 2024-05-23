
#include "compiler/frontend/ast/nodes.h"
#include "compiler/frontend/sema/check.h"

namespace snowball {
namespace frontend {
namespace sema {

void TypeChecker::visit(ast::BinaryOp* node) {
  auto& lhs = node->get_lhs().value();
  auto rhs = node->get_rhs();
  auto op = node->get_op();
  lhs->accept(this);
  if (rhs.has_value()) 
    rhs.value()->accept(this);
  if (op == Operator::Eq) {
    unify(lhs->get_type(), rhs.value()->get_type(), node->get_location());
    do_deduce(lhs);
  }

  auto lhs_type = lhs->get_type();
  if (lhs_type->is_int() || lhs_type->is_float()) {
    unify(node->get_type(), lhs->get_type(), node->get_location());
    // TODO: Implement the rest of the binary operators
    return;
  } 

  // TODO: Implement the rest of the binary operators
  // TODO: This following line is a temporary fix
  // unify(node->get_type(), lhs->get_type(), node->get_location());
  sn_assert(false, "BinaryOp not implemented for var_id");
}

}
}
}
