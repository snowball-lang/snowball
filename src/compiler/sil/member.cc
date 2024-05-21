
#include "compiler/sil/insts.h"
#include "compiler/sil/binder.h"

namespace snowball {
namespace sil {

void Binder::visit(ast::MemberAccess* node) {
  if (node->get_access_type() == ast::MemberAccess::Static || (!node->is_type_index() && node->get_var_id() != 0)) {
    auto var = var_ids.find(node->get_var_id());
    assert(var != var_ids.end());
    // note: Do not use get_type(node) here, because the type of the member access is the type of the member.
    //       node has no type if it's static.
    value = ValueUse::create(node->get_location(), var->second->get_type(), var->second);
    return;
  } else if (node->is_type_index()) {
    sn_assert(node->get_access_type() == ast::MemberAccess::Default, "Static member access with index");
    value = ValueIndex::create(node->get_location(), get_type(node), accept(node->get_object()), node->get_index());
    return;
  }
  sn_unreachable();
}

}
}
