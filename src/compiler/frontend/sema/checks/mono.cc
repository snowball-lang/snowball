
#include "compiler/frontend/ast/nodes.h"
#include "compiler/frontend/sema/check.h"

namespace snowball {
namespace frontend {
namespace sema {

using namespace utils;

ast::FnDecl* TypeChecker::monorphosize(ast::FnDecl*& node, const std::map<std::string, ast::types::Type*>& deduced, const SourceLocation& loc) {
  node->clear_generics();
  auto fn_ty_copy = node->get_type()->as_func();
  node->get_type() = nullptr;
  auto state = get_generic_context(node->get_generic_id());
  node->set_generic_instanced();
  if (vctx.debug_verbose) {
    std::string gen_str;
    for (auto& [name, type] : deduced)
      gen_str += "<" + name + ": " + type->get_printable_name() + ">, ";
    gen_str = gen_str.substr(0, gen_str.size() - 2);
    debug(F("Monorphosizing function {} with [{}]", node->get_name(), gen_str));
  }
  generic_registry[node->get_generic_id()].push_back(MonorphosizedFn {
    .decl = node,
    .generics = deduced
  });
  node->increment_id();  
  TypeCheckerContext backup = ctx;
  backup.scopes = universe.get_scopes();
  set_generic_context(state);
  universe.add_scope();
  for (auto& [name, type] : deduced) {
    universe.add_item(name, TypeCheckItem::create_type(type));
  }
  for (auto& param : node->get_params()) {
    param->get_type() = nullptr;
    assert(param->get_decl_type());
    auto ty = get_type(param->get_decl_type().value());
    unify(param->get_type(), ty, param->get_location());
  }
  auto ret = get_type(node->get_return_type());
  unify(node->get_type(), ast::types::FuncType::create(node, ret, fn_ty_copy->is_variadic()), node->get_location());
  node->accept(this);
  check_fn(node, true);
  if (node->get_body()) {
    node->get_body().value()->accept(this);
  }
  state.current_module->mutate_ast(node);
  universe.remove_scope();
  set_generic_context(backup);
  return node;
}

ast::ClassDecl* TypeChecker::monorphosize(ast::ClassDecl*& node, const std::map<std::string, ast::types::Type*>& generics, const SourceLocation& loc) {
  node->clear_generics();
  auto class_ty_copy = node->get_type()->as_class();
  node->get_type() = nullptr;
  auto state = get_generic_context(node->get_id());
  node->set_generic_instanced();
  if (vctx.debug_verbose) {
    std::string gen_str;
    for (auto& [name, type] : generics)
      gen_str += "<" + name + ": " + type->get_printable_name() + ">, ";
    gen_str = gen_str.substr(0, gen_str.size() - 2);
    debug(F("Monorphosizing class {} with [{}]", node->get_name(), gen_str));
  }
  generic_class_registry[node->get_id()].push_back(MonorphosizedClass {
    .decl = node,
    .generics = generics
  });
  node->increment_id();
  TypeCheckerContext backup = ctx;
  backup.scopes = universe.get_scopes();
  set_generic_context(state);
  universe.add_scope();
  std::vector<ast::types::Type*> new_generics;
  new_generics.reserve(node->get_generics().size());
  for (auto& [name, type] : generics) {
    universe.add_item(name, TypeCheckItem::create_type(type));
    new_generics.push_back(type);
  }
  for (auto& impl : node->get_implemented_interfaces()) {
    impl.set_internal_type(get_type(impl));
  }
  auto backup_class = ctx.current_class;
  ctx.current_class = node;
  unify(node->get_type(), ast::types::ClassType::create(node, class_ty_copy->get_path(), new_generics, class_ty_copy->get_location()), node->get_location());
  for (auto& var : node->get_vars()) {
    var->set_parent_type(node->get_type());
    var->accept(this);
  }
  for (auto& method : node->get_funcs()) {
    universe.add_scope();
    check_fn(method, true);
    method->set_parent_type(node->get_type());
    method->accept(this);
    universe.remove_scope();
  }
  ctx.current_class = backup_class;
  universe.remove_scope();
  state.current_module->mutate_ast(node);
  set_generic_context(backup);
  return node;
}

}
}
}
