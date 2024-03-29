
#include <vector>
#include <memory>

#include "compiler/frontend/location.h"
#include "compiler/frontend/ast/types.h"
#include "compiler/frontend/ast/nodes.h"
#include "compiler/frontend/sema/universe.h"
#include "compiler/frontend/sema/check.h"

namespace snowball {
namespace frontend {
namespace sema {

TypeChecker::TypeChecker(const Ctx& ctx, std::vector<Module>& modules) 
  : AstVisitor(ctx), Reporter(), modules(modules) {}

void TypeChecker::check() {
  register_builtins();
  try {
    for (auto& module : modules) {
      ctx.current_module = &module;
      universe.add_scope();
      allowed_uuids.push_back(module.get_path());
      generate_global_scope(module.get_ast());
      allowed_uuids.pop_back();
      universe.remove_scope();
    }
    for (auto& module : modules) {
      ctx.current_module = &module;
      universe.add_scope();
      allowed_uuids.push_back(module.get_path());
      for (auto& stmt : module.get_ast()) {
        stmt->accept(this);
      }
      allowed_uuids.pop_back();
      universe.remove_scope();
    }
  } catch (const StopTypeChecking&) {
    // Do nothing
  }
}

void TypeChecker::err(const LocationHolder& holder, const std::string& message, 
    const Error::Info& info, Error::Type type, bool fatal) {
  if (ctx.current_function && ctx.current_function->is_generic_instanced()) {
    return; // skip duplicated errors from generic insatnce intantiations
  }
  add_error(E(message, holder.get_location(), info, type));
  if (fatal && type != Error::Type::Warn)
    throw StopTypeChecking();
}

void TypeChecker::register_builtins() {
  universe.add_item("i8", TypeCheckItem::create_type(ast::types::IntType::create_i8()));
  universe.add_item("i16", TypeCheckItem::create_type(ast::types::IntType::create_i16()));
  universe.add_item("i32", TypeCheckItem::create_type(ast::types::IntType::create_i32()));
  universe.add_item("i64", TypeCheckItem::create_type(ast::types::IntType::create_i64()));
  universe.add_item("u8", TypeCheckItem::create_type(ast::types::IntType::create_u8()));
  universe.add_item("u16", TypeCheckItem::create_type(ast::types::IntType::create_u16()));
  universe.add_item("u32", TypeCheckItem::create_type(ast::types::IntType::create_u32()));
  universe.add_item("u64", TypeCheckItem::create_type(ast::types::IntType::create_u64()));
  universe.add_item("f32", TypeCheckItem::create_type(ast::types::FloatType::create_f32()));
  universe.add_item("f64", TypeCheckItem::create_type(ast::types::FloatType::create_f64()));
  universe.add_item("bool", TypeCheckItem::create_type(ast::types::IntType::create(1, false)));
  universe.add_item("void", TypeCheckItem::create_type(ast::types::VoidType::create()));
}

NamespacePath TypeChecker::get_namespace_path(const std::string& name) {
  auto path = ctx.current_module->get_path();
  path.push(name);
  // TODO: Classes, etc.
  return path;
}

void TypeChecker::define_variable(ast::VarDecl* node, const SourceLocation& loc) {
  if (universe.current_scope().get_item(node->get_name()).has_value()) {
    err(node->get_location(), fmt::format("Variable '{}' already defined in this scope", node->get_name()),
    Error::Info {
      .highlight = fmt::format("Variable '{}' already defined", node->get_name()),
      .help = fmt::format("Did you mean to use the variable '{}' instead of defining it?", node->get_name()),
      .note = "You can create a new lexical scope to define a new variable with the same name."
    }, Error::Type::Err, false);
  }
  universe.add_item(node->get_name(), TypeCheckItem::create_var(node));
  universe.add_var_id(node->get_id(), node);
}

ast::types::UnknownType* TypeChecker::get_unknown_type() {
  return ast::types::UnknownType::create(universe.get_constraints());
}

ast::types::ErrorType* TypeChecker::get_error_type() {
  return ast::types::ErrorType::create();
}

TypeCheckerContext& TypeChecker::get_generic_context(uint64_t id) {
  auto it = generic_contexts.find(id);
  sn_assert(it != generic_contexts.end(), "Generic context not found");
  return it->second;
}

TypeCheckerContext& TypeChecker::create_generic_context(uint64_t id) {
  auto ctx = TypeCheckerContext {
    .allowed_uuids = this->ctx.allowed_uuids,
    .current_module = this->ctx.current_module,
    .current_function = this->ctx.current_function,
    .scopes = universe.get_scopes()
  };
  generic_contexts[id] = ctx;
  return generic_contexts[id];
}

void TypeChecker::set_generic_context(const TypeCheckerContext& ctx) { 
  universe.get_scopes() = ctx.scopes; 
  this->ctx = ctx;
}

}
}
}
