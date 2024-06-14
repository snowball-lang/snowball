
#include "compiler/frontend/ast/nodes.h"
#include "compiler/frontend/sema/check.h"

namespace snowball {
namespace frontend {
namespace sema {

void TypeChecker::visit(ast::Return* node) {
  if (!ctx.current_function) {
    err(node->get_location(), "Found return statement outside of function", Error::Info {
      .highlight = "No function context",
      .note = "Return statements can only be used inside functions"
    });
    unify(node->get_type(), get_error_type());
  }
  auto function_type = ctx.current_function->get_type()->as_func();
  assert(function_type && "Function type is not a function type");
  if (!node->get_value() && !function_type->get_return_type()->is_void()) {
    err(node->get_location(), "Expected return value", Error::Info {
      .highlight = "Expected return value",
      .note = "Function expects a return value because it's return type is not void"
    });
    unify(node->get_type(), get_error_type());
    return;
  } else if (node->get_value() && function_type->get_return_type()->is_void()) {
    err(node->get_location(), "Unexpected return value", Error::Info {
      .highlight = "Unexpected return value",
      .note = "Function does not expect a return value because it's return type is void"
    });
    unify(node->get_type(), get_error_type());
    return;
  }
  if (node->get_value()) {
    node->get_value().value()->accept(this);
    auto expr_type = node->get_value().value()->get_type();
    if (expr_type->is_error()) {
      unify(node->get_type(), expr_type, node->get_location());
      return;
    }
    unify(node->get_type(), function_type->get_return_type(), node->get_location());
    unify(expr_type, function_type->get_return_type(), node->get_location());
  } else {
    unify(node->get_type(), function_type->get_return_type(), node->get_location());
  }
} 

}
}
}
