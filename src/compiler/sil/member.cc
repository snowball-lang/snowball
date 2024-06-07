
#include "compiler/sil/insts.h"
#include "compiler/sil/binder.h"

namespace snowball {
namespace sil {

void Binder::visit(ast::MemberAccess* node) {
  if (node->get_access_type() == ast::MemberAccess::Static) {
    auto var = var_ids.find(node->get_var_id());
    assert(var != var_ids.end());
    // note: Do not use get_type(node) here, because the type of the member access is the type of the member.
    //       node has no type if it's static.
    value = ValueUse::create(node->get_location(), var->second->get_type(), var->second);
    return;
  }
  auto var_inst = accept(node->get_member())->as<ValueUse>();
  sn_assert(var_inst, "Member access on non-val-use");
  if (auto func = var_inst->get_value()->as<FuncDecl>()) {
    value = ValueUse::create(node->get_location(), func->get_type(), func);
    return;
  }
  auto var = var_inst->get_value()->as<VarDecl>();
  sn_assert(var, "Member access on non-variable");
  auto var_idx = var->get_index();
  value = ValueIndex::create(node->get_location(), get_type(node), accept(node->get_object()), var_idx.value());
}

}
}
