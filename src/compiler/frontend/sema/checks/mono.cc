
#include "compiler/frontend/ast/nodes.h"
#include "compiler/frontend/sema/check.h"

#include "compiler/globals.h"

namespace snowball {
namespace frontend {
namespace sema {

using namespace utils;

ast::FnDecl* TypeChecker::monorphosize(ast::FnDecl*& node, const llvm::StringMap<ast::types::Type*>& deduced, const SourceLocation& loc) {
  node->clear_generics();
  auto fn_ty_copy = node->get_type()->as_func();
  node->get_type() = nullptr;
  auto state = get_generic_context(node->get_generic_id());
  node->set_generic_instanced();
  if (global.debug_verbose) {
    std::string gen_str;
    for (auto& [name, type] : deduced)
      gen_str += "<" + name.str() + ": " + type->get_printable_name() + ">, ";
    gen_str = gen_str.substr(0, gen_str.size() - 2);
    debug(F("Monorphosizing function {} with [{}]", node->get_name(), gen_str));
  }
  generic_registry[node->get_generic_id()].push_back(MonorphosizedFn {
    .decl = node,
    .generics = deduced
  });
  node->increment_id();  
  auto backup = create_generic_context(0, true);
  set_generic_context(state);
  enter_scope();
  auto backup_func = ctx.current_function;
  ctx.current_function = node;
  for (auto& [name, type] : deduced) {
    universe.add_item(name.str(), TypeCheckItem::create_type(type));
  }
  for (auto& param : node->get_params()) {
    param->get_type() = nullptr;
    assert(param->get_decl_type());
    auto ty = get_type(param->get_decl_type().value());
    unify(param->get_type(), ty, param->get_location());
  }
  auto ret = get_type(node->get_return_type());
  unify(node->get_type(), ast::types::FuncType::create(node, ret, fn_ty_copy->is_variadic(), fn_ty_copy->is_unsafe()), node->get_location());
  node->accept(this);
  check_fn(node, true);
  if (node->get_body()) {
    node->get_body().value()->accept(this);
  }
  state.current_module->mutate_ast(node);
  ctx.current_function = backup_func;
  exit_scope();
  set_generic_context(backup);
  return node;
}

ast::ClassDecl* TypeChecker::monorphosize(ast::ClassDecl*& node, const llvm::StringMap<ast::types::Type*>& generics, const SourceLocation& loc) {
  node->clear_generics();
  auto class_ty_copy = node->get_type()->as_class();
  node->get_type() = nullptr;
  auto state = get_generic_context(node->get_id());
  node->set_generic_instanced();
  if (global.debug_verbose) {
    std::string gen_str;
    for (auto& [name, type] : generics)
      gen_str += "<" + name.str() + ": " + type->get_printable_name() + ">, ";
    gen_str = gen_str.substr(0, gen_str.size() - 2);
    debug(F("Monorphosizing class {} with [{}]", node->get_name(), gen_str));
  }
  generic_class_registry[node->get_id()].push_back(MonorphosizedClass {
    .decl = node,
    .generics = generics
  });
  node->increment_id();
  auto backup = create_generic_context(0, true);
  set_generic_context(state);
  enter_scope();
  auto backup_class = ctx.current_class;
  std::vector<ast::types::Type*> new_generics;
  new_generics.reserve(node->get_generics().size());
  for (auto& [name, type] : generics) {
    universe.add_item(name.str(), type);
    new_generics.push_back(type);
  }
  unify(node->get_type(), ast::types::ClassType::create(node, class_ty_copy->get_path(), new_generics, class_ty_copy->get_location()), node->get_location());
  ctx.current_class = node->get_type();
  update_self_type();
  for (auto& impl : node->get_implemented_interfaces()) {
    impl.set_internal_type(get_type(impl));
  }
  for (auto& var : node->get_vars()) {
    var->set_parent_type(node->get_type());
    var->accept(this);
  }
  for (auto& method : node->get_funcs()) {
    enter_scope();
    check_fn(method, true);
    method->set_parent_type(node->get_type());
    exit_scope();
  }
  for (auto& method : node->get_funcs()) {
    enter_scope();
    method->accept(this);
    exit_scope();
  }
  check_implementations(node); // For updating the vtable indexes
  ctx.current_class = backup_class;
  (void)exit_scope();
  state.current_module->mutate_ast(node);
  set_generic_context(backup);
  return node;
}

}
}
}
