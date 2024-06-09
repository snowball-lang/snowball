
#include "compiler/frontend/ast/nodes.h"
#include "compiler/frontend/sema/check.h"

namespace snowball {
namespace frontend {
namespace sema {

void TypeChecker::visit(ast::Block* node) {
  enter_scope();
  for (auto& stmt : node->get_stmts()) {
    stmt->accept(this);
  }
  auto [errors, clean_status] = exit_scope();
  sn_assert(errors.empty(), "got errors after exiting borrow scope");
  for (auto& dropped : clean_status.get_dropped()) {
    auto var = universe.get_var_id(dropped).value()->as<ast::VarDecl>();
    debug(F("  \t[borrow]\tDroping variable with name: {}", var->get_name()));
  }
}

}
}
}
