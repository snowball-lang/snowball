
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
  auto state = get_generic_context(node->get_id());
  node->set_generic_instanced();
  generic_registry[node->get_id()].push_back(MonorphosizedFn {
    .decl = node,
    .generics = deduced
  });
  node->increment_id();  
  auto backup = ctx;
  backup.scopes = universe.get_scopes();
  set_generic_context(state);
  universe.add_scope();
  for (auto& [name, type] : deduced) {
    universe.add_item(name, TypeCheckItem::create_type(type));
  }
  std::vector<ast::types::Type*> params;
  params.reserve(node->get_params().size());
  for (auto& param : node->get_params()) {
    param->get_type() = nullptr;
    assert(param->get_decl_type());
    params.push_back(get_type(param->get_decl_type().value()));
    unify(param->get_type(), params.back(), param->get_location());
  }
  auto ret = get_type(node->get_return_type());
  unify(node->get_type(), ast::types::FuncType::create(params, ret, fn_ty_copy->is_variadic()), node->get_location());
  node->accept(this);
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
  generic_class_registry[node->get_id()].push_back(MonorphosizedClass {
    .decl = node,
    .generics = generics
  });
  node->increment_id();
  auto backup = ctx;
  backup.scopes = universe.get_scopes();
  set_generic_context(state);
  universe.add_scope();
  std::vector<ast::types::Type*> new_generics;
  new_generics.reserve(node->get_generics().size());
  for (auto& [name, type] : generics) {
    universe.add_item(name, TypeCheckItem::create_type(type));
    new_generics.push_back(type);
  }
  for (auto& var : node->get_vars()) {
    var->accept(this);
  }
  for (auto& method : node->get_funcs()) {
    method->accept(this);
  }
  unify(node->get_type(), ast::types::ClassType::create(node, class_ty_copy->get_path(), new_generics, class_ty_copy->get_location()), node->get_location());
  universe.remove_scope();
  set_generic_context(backup);
  return node;
}

}
}
}