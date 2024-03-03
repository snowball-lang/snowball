
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
    accept(param);
  }
  auto body = accept(node->get_body());
  assert(body->is<Block>());
  auto func = FuncDecl::create(node->get_location(), type, name, sil_params, *node, body->as<Block>(), node->get_id());
  current_module.add_fn_decl(func);
  value = func;
}

}
}
