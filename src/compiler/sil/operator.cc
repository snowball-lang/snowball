
#include "compiler/sil/insts.h"
#include "compiler/sil/binder.h"

namespace snowball {
namespace sil {

void Binder::visit(ast::BinaryOp* node) {
  if (auto call = node->get_call()) {
    value = accept(call.value());
    return;
  }
  std::optional<Inst*> rhs;
  if (node->get_rhs().has_value()) {
    rhs = accept(node->get_rhs().value());
  }
  value = BinaryOp::create(node->get_location(), get_type(node), accept(node->get_lhs().value()), node->get_op(), rhs);
}

}
}
