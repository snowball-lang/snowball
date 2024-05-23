
#include "compiler/sil/insts.h"
#include "compiler/sil/binder.h"

namespace snowball {
namespace sil {

void Binder::visit(ast::BinaryOp* node) {
  if (node->get_var_id() != 0) {
    sn_assert(false, "BinaryOp not implemented for var_id");
  }
  std::optional<Inst*> rhs;
  if (node->get_rhs().has_value()) {
    rhs = accept(node->get_rhs().value());
  }
  value = BinaryOp::create(node->get_location(), get_type(node), accept(node->get_lhs().value()), node->get_op(), rhs);
}

}
}
