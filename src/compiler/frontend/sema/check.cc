
#include <vector>
#include <memory>

#include "compiler/frontend/location.h"
#include "compiler/frontend/ast/types.h"
#include "compiler/frontend/ast/nodes.h"
#include "compiler/frontend/sema/universe.h"
#include "compiler/frontend/sema/check.h"

#include "compiler/globals.h"

namespace snowball {
namespace frontend {
namespace sema {

TypeChecker::TypeChecker(const Ctx& ctx, std::vector<Module>& modules) 
  : AstVisitor(ctx), Reporter(), modules(modules) {}

void TypeChecker::check() {
  register_builtins();
  try {
    for (bool first = true;; first = false) {
      for (auto& module : modules) {
        ctx.current_module = &module;
        universe.add_scope();
        ctx.allowed_uuids.push_back(module.get_path());
        generate_global_scope(module.get_ast(), first);
        ctx.allowed_uuids.pop_back();
        universe.remove_scope();
      }
      if (!first) break;
    }
    if (get_error_count() > 0)
      throw StopTypeChecking();
    for (auto& module : modules) {
      ctx.current_module = &module;
      universe.add_scope();
      ctx.allowed_uuids.push_back(module.get_path());
      auto& ast = module.get_ast();
      for (size_t i = 0; i < ast.size(); i++) {
        ast[i]->accept(this);
      }
      ctx.allowed_uuids.pop_back();
      universe.remove_scope();
    }
    post_check();
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

void TypeChecker::post_check() {
  if (get_error_count() > 0)
    return;

  if (global.emit_type == EmitType::Executable && !has_entry_declared) {
    err(SourceLocation(0, 0, 0, std::make_shared<SourceFile>()), "No entry point function found!", Error::Info {
      .highlight = "No main function found",
      .help = "You need to define a main function to compile an executable"
    }, Error::Type::Err, true);    
  }
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
  if (ctx.current_class)
    path.push(ctx.current_class->get_name());
  return path;
}

void TypeChecker::define_variable(ast::VarDecl* node, const SourceLocation& loc, bool initialized) {
  if (universe.current_scope().get_item(node->get_name()).has_value()) {
    err(node->get_location(), fmt::format("Variable '{}' already defined in this scope", node->get_name()),
    Error::Info {
      .highlight = fmt::format("Variable '{}' already defined", node->get_name()),
      .help = fmt::format("Did you mean to use the variable '{}' instead of defining it?", node->get_name()),
      .note = "You can create a new lexical scope to define a new variable with the same name."
    }, Error::Type::Err, false);
  }
  auto item = TypeCheckItem::create_var(node);
  if (initialized) {
    item.set_initialized();
  } else item.set_uninitialized();
  universe.add_item(node->get_name(), item);
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
    .current_class = this->ctx.current_class,
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
