
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
      current_module = &module;
      universe.add_scope();
      generate_global_scope(module.get_ast());
      universe.remove_scope();
    }
    for (auto& module : modules) {
      current_module = &module;
      universe.add_scope();
      for (auto& stmt : module.get_ast()) {
        stmt->accept(this);
      }
      universe.remove_scope();
    }
  } catch (const StopTypeChecking&) {
    // Do nothing
  }
}

void TypeChecker::err(const LocationHolder& holder, const std::string& message, 
    const Error::Info& info, Error::Type type, bool fatal) {
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
  auto path = current_module->get_path();
  path.push(name);
  // TODO: Classes, etc.
  return path;
}

void TypeChecker::define_variable(ast::VarDecl* node) {
  universe.add_item(node->get_name(), TypeCheckItem::create_var(node));
  universe.add_var_id(node->get_id(), node);
}

ast::types::UnknownType* TypeChecker::get_unknown_type() {
  return ast::types::UnknownType::create(universe.get_constraints());
}

}
}
}
