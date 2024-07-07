
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
    }, Error::Type::Err, false);
    unify(node->get_type(), get_error_type());
    return;
  }
  auto function_type = ctx.current_function->get_type()->as_func();
  assert(function_type && "Function type is not a function type");
  if (!node->get_value() && !function_type->get_return_type()->is_void()) {
    err(node->get_location(), "Expected return value", Error::Info {
      .highlight = "Expected return value",
      .note = "Function expects a return value because it's return type is not void"
    }, Error::Type::Err, false);
    unify(node->get_type(), get_error_type());
    return;
  } else if (node->get_value() && function_type->get_return_type()->is_void()) {
    err(node->get_location(), "Unexpected return value", Error::Info {
      .highlight = "Unexpected return value",
      .note = "Function does not expect a return value because it's return type is void"
    }, Error::Type::Err, false);
    unify(node->get_type(), get_error_type());
    return;
  }
  if (node->get_value()) {
    infer_ctx.type = function_type->get_return_type();
    node->get_value().value()->accept(this);
    infer_ctx.clear();
    auto expr_type = node->get_value().value()->get_type();
    if (expr_type->is_error()) {
      unify(node->get_type(), expr_type, node->get_location());
      return;
    }
    try_cast(node->get_value().value(), function_type->get_return_type());
    unify(node->get_type(), function_type->get_return_type(), node->get_location());
    unify(node->get_type(), node->get_value().value()->get_type(), node->get_location());
  } else {
    unify(node->get_type(), function_type->get_return_type(), node->get_location());
  }
} 

}
}
}
