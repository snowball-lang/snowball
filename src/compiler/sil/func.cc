
#include <cassert>

#include "compiler/sil/insts.h"
#include "compiler/sil/binder.h"

namespace snowball {
namespace sil {

void Binder::visit(ast::FnDecl* node) {
  auto type = node->get_type();
  auto name = node->get_name();
  auto params = node->get_params();
  auto body = accept(node->get_body());
  assert(body->is<Block>());
  auto sil_params = std::vector<std::string>();
  for (auto& param : params)
    sil_params.push_back(param.name);
  auto func = FuncDecl::create(type, name, sil_params, *node, body->as<Block>());
  current_module.add_fn_decl(func);
  value = func;
}

}
}
