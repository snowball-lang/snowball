
#include "compiler/frontend/ast/nodes.h"
#include "compiler/frontend/sema/check.h"

namespace snowball {
namespace frontend {
namespace sema {

void TypeChecker::visit(ast::VarDecl* node) {
  if (auto type = node->get_decl_type()) {
    unify(node->get_type(), get_type(type.value()));
    // TODO: add type to the infer context
  }
  if (auto expr = node->get_value()) {
    expr.value()->accept(this);
    if (!node->get_decl_type()) {
      unify(node->get_type(), expr.value()->get_type());
    }
  }
  if (!node->get_decl_type() && !node->get_value()) {
    unify(node->get_type(), get_unknown_type());
  }
  define_variable(node);
}

}
}
}
