
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
  for (auto& module : modules) {
    try {
      current_module = &module;
      universe.add_scope();
      generate_global_scope(module.get_ast());

      for (auto& stmt : module.get_ast()) {
        stmt->accept(this);
      }
      universe.remove_scope();
    } catch (const StopTypeChecking&) {
      continue;
    }
  }
}

void TypeChecker::err(const LocationHolder* holder, const std::string& message, 
    const Error::Info& info, Error::Type type, bool fatal) {
  add_error(E(message, holder->get_location(), info, type));
  if (fatal && type != Error::Type::Warn)
    throw StopTypeChecking();
}

void TypeChecker::register_builtins() {
  universe.add_item("i8", TypeCheckItem::create(ast::types::IntType::create_i8()));
  universe.add_item("i16", TypeCheckItem::create(ast::types::IntType::create_i16()));
  universe.add_item("i32", TypeCheckItem::create(ast::types::IntType::create_i32()));
  universe.add_item("i64", TypeCheckItem::create(ast::types::IntType::create_i64()));
  universe.add_item("u8", TypeCheckItem::create(ast::types::IntType::create_u8()));
  universe.add_item("u16", TypeCheckItem::create(ast::types::IntType::create_u16()));
  universe.add_item("u32", TypeCheckItem::create(ast::types::IntType::create_u32()));
  universe.add_item("u64", TypeCheckItem::create(ast::types::IntType::create_u64()));
  universe.add_item("f32", TypeCheckItem::create(ast::types::FloatType::create_f32()));
  universe.add_item("f64", TypeCheckItem::create(ast::types::FloatType::create_f64()));
}

NamespacePath TypeChecker::get_namespace_path(const std::string& name) {
  auto path = current_module->get_path();
  path.push(name);
  // TODO: Classes, etc.
  return path;
}

}
}
}
