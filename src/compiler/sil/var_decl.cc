
#include "compiler/sil/insts.h"
#include "compiler/sil/binder.h"

namespace snowball {
namespace sil {

void Binder::visit(ast::VarDecl* node) {
  get_type(node);
  std::optional<sil::Inst*> var_value = std::nullopt;
  if (auto value = node->get_value())
    var_value = accept(value.value());
  value = VarDecl::create(node->get_location(), node->get_type(), node->get_name(), *node, var_value, node->get_id());
  var_ids.insert({node->get_id(), value});
}

}
}
