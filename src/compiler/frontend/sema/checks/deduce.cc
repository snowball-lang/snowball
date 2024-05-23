
#include "compiler/frontend/ast/nodes.h"
#include "compiler/frontend/sema/check.h"

namespace snowball {
namespace frontend {
namespace sema {

void TypeChecker::do_deduce(ast::Expr* expr) {
  if (auto ident = expr->as<ast::Ident>()) {
    auto var = ident->get_var_id();
    if (var != 0) {
      auto decl = universe.get_var_id(var);
      sn_assert(decl.has_value(), "Variable not found for deduce");
      auto& var_decl = decl.value();
      auto& type = var_decl->get_type();
      unify(type, ident->get_type(), ident->get_location());
      if (auto as_var = var_decl->as<ast::VarDecl>()) {
        if (auto arg_for = as_var->get_arg_for()) {
          arg_for.value()->get_type()->as_func()->recalibrate_cache();
        }
      }
    }
  }
}

}
}
}
