
#include "compiler/frontend/ast/nodes.h"
#include "compiler/frontend/sema/check.h"

namespace snowball {
namespace frontend {
namespace sema {

void TypeChecker::visit(ast::BinaryOp* node) {
  auto& lhs = node->get_lhs().value();
  auto rhs = node->get_rhs();
  auto op = node->get_op();
  if (auto ident = lhs->as<ast::Ident>(); ident && op == Operator::Eq) {
    ident->set_used_as_assignee();
  }
  lhs->accept(this);
  if (rhs.has_value()) 
    rhs.value()->accept(this);
  if (op == Operator::Eq) {
    unify(lhs->get_type(), rhs.value()->get_type(), node->get_location());
    auto stmt = do_deduce(lhs);
    if (!is_mutable(lhs, stmt)) {
      do_deduce(lhs);
      err(node->get_location(), "Cannot assign to immutable variable", Error::Info {
        .highlight = "Symbol not mutable",
        .help = "Make sure the variable is mutable",
        .see = "https://snowball-lang.gitbook.io/docs/language-reference/types/mutability"
      }, Error::Type::Err, false);
    }
    if (auto var = (!stmt) ? nullptr : stmt->as<ast::VarDecl>(); var && !var->get_member_index().has_value()) {
      borrow_checker.init_variable(var->get_id());
    }
    if (auto var = do_deduce(rhs.value(), true)->as<ast::VarDecl>(); 
      var && !var->get_member_index().has_value()) {
      set_moved_var(var); // This will handle if the type contains a move-only type
    }
    unify(node->get_type(), lhs->get_type(), node->get_location());
    return;
  }

  auto lhs_type = try_get_unknown(lhs->get_type());
  if (lhs_type->is_int() || lhs_type->is_float()) {
    switch (op) {
      case Operator::Eqeq:
      case Operator::Noteq:
      case Operator::Lt:
      case Operator::Lteq:
      case Operator::Gt:
      case Operator::Gteq:
      case Operator::And:
      case Operator::Or:
      case Operator::Not:
      case Operator::BitAnd:
      case Operator::BitOr:
      case Operator::BitXor:
      case Operator::BitNot:
        unify(node->get_type(), get_type("bool"), node->get_location());
        break;
      default:
        unify(node->get_type(), lhs_type, node->get_location());
        break;
    }
    // TODO: Implement the rest of the binary operators
    return;
  } 

  // unify(node->get_type(), lhs->get_type(), node->get_location());
  // Create a call to the operator function
  std::vector<ast::Expr*> args;
  if (rhs.has_value()) {
    args.push_back(rhs.value());
  }
  auto call = ast::Call::create(node->get_location(), 
    ast::MemberAccess::create(node->get_location(), 
      lhs,
      ast::Ident::create(node->get_location(), op_to_string(op))),
    args
  );
  call->accept(this);
  node->set_call(call);
  unify(node->get_type(), call->get_type(), node->get_location());
}

std::string TypeChecker::op_to_string(Operator op) {
#define DEFINE_OP(_1, _2, _3)
#define DEFINE_OP_NAME(o, n) \
  case Operator::o: return "$" n;
  switch (op) {
#include "compiler/frontend/ast/operators.def"
  }
  sn_unreachable();
#undef DEFINE_OP_NAME
}

std::string TypeChecker::printable_op(std::string op) {
  if (op[0] == '$') {
    return "operator " + op.substr(1);
  }
  return op;
}


}
}
}
