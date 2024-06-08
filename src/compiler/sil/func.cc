
#include <cassert>

#include "compiler/sil/insts.h"
#include "compiler/sil/binder.h"

namespace snowball {
namespace sil {

void Binder::visit(ast::FnDecl* node) {
  auto type = get_type(node);
  auto name = node->get_name();
  auto params = node->get_params();
  // We need to declare the function first, this is because we need to know the
  // all the functions before we can bind them together. This allows us 
  // to call functions before they are declared.
  if (just_declare) {
    auto sil_params = std::vector<std::pair<uint64_t, std::string>>();
    for (auto& gen : node->get_generics()) {
      for (auto& constraint : gen.get_constraints()) {
        (void)get_type(constraint.get_internal_type().value(), constraint.get_location());
      }
    }
    for (auto param : params) {
      sil_params.push_back({param->get_id(), param->get_name()});
    }
    auto func = FuncDecl::create(node->get_location(), type, name, sil_params, current_module, *node, std::nullopt, node->get_id());
    var_ids.insert({node->get_id(), func});
    value = func;
    return;
  }
  
  auto func = (sil::FuncDecl*)var_ids.find(node->get_id())->second;  
  auto backup = ctx.ast_current_func;
  auto backup2 = ctx.current_func;
  ctx.ast_current_func = node;
  ctx.current_func = func;
  for (auto param : params) {
    accept(param);
  }
  if (auto block = node->get_body()) {
    auto body = accept(block.value());
    assert(body->is<Block>());
    func->set_body(body->as<Block>());
  }
  if (node->should_generate()) {
    current_module->add_fn_decl(func);
  }
  ctx.ast_current_func = backup;
  ctx.current_func = backup2;
  if (auto parent = node->get_parent_type()) {
    auto parent_type = parent.value();
    func->set_parent_type(parent_type);
  }
  value = func;
}

std::string FuncDecl::get_mangled_name() const {
  if (get_link_name()) {
    return get_link_name().value();
  }
  auto type = get_type()->as_func();
  assert(type);
  auto name = get_name();
  auto type_mangle = type->get_mangled_name();
  std::string parent_type_mangle;
  if (parent_type) {
    parent_type_mangle = "_P" + parent_type.value()->get_mangled_name();
  }
  return fmt::format("_ZSN{}{}{}{}{}.{}", parent_type_mangle, name.size(), name, type_mangle.size(), type_mangle, get_id());
}

std::string FuncDecl::get_printable_name() const {
  std::string base = parent_module->get_path().get_path_string();
  if (parent_type) {
    // The parent type already includes the module path
    base = parent_type.value()->get_printable_name();
  }
  return fmt::format("{}::{}", base, get_name());
}

}
}
