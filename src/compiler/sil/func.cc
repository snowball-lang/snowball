
#include <cassert>

#include "compiler/sil/insts.h"
#include "compiler/sil/binder.h"

namespace snowball {
namespace sil {

void Binder::visit(ast::FnDecl* node) {
  auto type = get_type(node);
  auto name = node->get_name();
  auto params = node->get_params();
  auto sil_params = std::vector<std::pair<uint64_t, std::string>>();
  for (auto param : params) {
    sil_params.push_back({param->get_id(), param->get_name()});
  }
  if (just_declare) {
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
  if (ctx.ast_current_class) {
    auto cls = ctx.ast_current_class.value();
    func->set_parent_type(cls->get_type());
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
  return fmt::format("_ZSN{}{}{}{}.{}", name.size(), name, type_mangle.size(), type_mangle, get_id());
}

std::string FuncDecl::get_printable_name() const {
  std::string base = parent_module->get_path().get_path_string();
  // TODO: check if it's inside a class!
  return fmt::format("{}::{}", base, get_name());
}

}
}
