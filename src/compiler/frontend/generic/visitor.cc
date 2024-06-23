
#include "compiler/frontend/generic/visitor.h"

namespace snowball {
namespace frontend {

GenericVisitor::GenericVisitor(const Ctx& ctx, std::vector<Module>& modules)
  : AstVisitor(ctx), modules(modules) {
}

void GenericVisitor::visit() {
  for (auto& module : modules) {
    for (auto& node : module.get_ast()) {
      node->accept(this);
    }
  }
}

void GenericVisitor::visit(ast::Block* node) {
  for (auto& stmt : node->get_stmts()) {
    stmt->accept(this);
  }
}

void GenericVisitor::visit(ast::FnDecl* node) {
  auto old = ctx.current_function;
  ctx.current_function = node;
  for (auto& param : node->get_params()) {
    param->accept(this);
  }
  if (node->get_body()) {
    node->get_body().value()->accept(this);
  }
  ctx.current_function = old;
}

void GenericVisitor::visit(ast::Ident* node) {
  // Do nothing
}

void GenericVisitor::visit(ast::Number* node) {
  // Do nothing
}

void GenericVisitor::visit(ast::VarDecl* node) {
  if (node->get_value()) {
    node->get_value().value()->accept(this);
  }
}

void GenericVisitor::visit(ast::Call* node) {
  node->get_callee()->accept(this);
  for (auto& arg : node->get_args()) {
    arg->accept(this);
  }
}

void GenericVisitor::visit(ast::ClassDecl* node) {
  auto old = ctx.current_class;
  ctx.current_class = node;
  for (auto& field : node->get_vars()) {
    field->accept(this);
  }
  for (auto& method : node->get_funcs()) {
    method->accept(this);
  }
  ctx.current_class = old;
}

void GenericVisitor::visit(ast::BinaryOp* node) {
  if (node->get_lhs()) {
    node->get_lhs().value()->accept(this);
  }
  if (node->get_rhs()) {
    node->get_rhs().value()->accept(this);
  }
}

void GenericVisitor::visit(ast::MemberAccess* node) {
  node->get_object()->accept(this);
  node->get_member()->accept(this);
}

void GenericVisitor::visit(ast::Reference* node) {
  node->get_expr()->accept(this);
}

void GenericVisitor::visit(ast::Dereference* node) {
  node->get_expr()->accept(this);
}

void GenericVisitor::visit(ast::String* node) {
  // Do nothing
}

void GenericVisitor::visit(ast::Use* node) {
  // Do nothing
}

void GenericVisitor::visit(ast::NewExpr* node) {
  visit(node->as<ast::Call>());
}

void GenericVisitor::visit(ast::Return* node) {
  if (node->get_value()) {
    node->get_value().value()->accept(this);
  }
}

void GenericVisitor::err(const LocationHolder& holder, const std::string& message,
      const Error::Info& info, Error::Type type) {
  if (shoudnt_error()) {
    return; // skip duplicated errors from generic instance instantiations
  }
  add_error(E(message, holder.get_location(), info, type));
}

bool GenericVisitor::shoudnt_error() const {
  return (ctx.current_function.has_value() && ctx.current_function.value()->is_generic_instanced())
      || (ctx.current_class.has_value() && ctx.current_class.value()->is_generic_instanced());
}

void GenericVisitor::warn(const LocationHolder& holder, const std::string& message,
      const Error::Info& info) {
  err(holder, message, info, Error::Type::Warn);
}

} // namespace frontend
} // namespace snowball
