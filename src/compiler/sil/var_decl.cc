
#include "compiler/sil/insts.h"
#include "compiler/sil/binder.h"
#include "compiler/frontend/ast/nodes.h"

namespace snowball {
namespace sil {

using Extern = frontend::ast::AttributedNode::Extern;

void Binder::visit(ast::VarDecl* node) {
  auto ty = get_type(node);
  std::optional<sil::Inst*> var_value = std::nullopt;
  if (auto value = node->get_value()) {
    var_value = accept(value.value());
  }
  auto var = VarDecl::create(node->get_location(), ty, node->get_name(), *node, var_value, node->get_id());
  if (node->get_member_index()) {
    var->set_index(node->get_member_index().value());
  }
  value = var;
  var_ids.insert({node->get_id(), value});
}

}
}
