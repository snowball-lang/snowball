
#include "compiler/frontend/ast/nodes.h"
#include "compiler/frontend/sema/check.h"

namespace snowball {
namespace frontend {
namespace sema {

ast::Stmt* TypeChecker::do_deduce(ast::Expr* expr) {
  if (auto ident = expr->as<ast::Ident>()) {
    auto var = ident->get_var_id();
    if (var != 0) {
      auto decl = universe.get_var_id(var);
      sn_assert(decl.has_value(), "Variable not found for deduce");
      auto& var_decl = decl.value();
      auto& type = var_decl->get_type();
      unify(type, expr->get_type(), ident->get_location());
      if (auto as_var = var_decl->as<ast::VarDecl>()) {
        if (auto arg_for = as_var->get_arg_for()) {
          arg_for.value()->get_type()->as_func()->recalibrate_cache();
        }
        return as_var;
      }
    }
  } else if (auto idx = expr->as<ast::MemberAccess>()) {
    // We do not want to deduce a member access, as it is not a variable
    // but we do want to return the variable that the member access is based on
    auto var = idx->get_var_id();
    if (var != 0) {
      return universe.get_var_id(var).value();
    }
  }
  return nullptr;
}

bool TypeChecker::is_mutable(ast::Expr* expr, ast::Stmt* stmt) {
  if (!stmt) return false;
  if (auto as_var = stmt->as<ast::VarDecl>()) {
    return as_var->get_mut();
  }
  // TODO: More cases
  return stmt->get_type()->is_mutable_type();
}

}
}
}
