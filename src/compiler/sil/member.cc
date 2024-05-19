
#include "compiler/sil/insts.h"
#include "compiler/sil/binder.h"

namespace snowball {
namespace sil {

void Binder::visit(ast::MemberAccess* node) {
  if (node->get_access_type() == ast::MemberAccess::Static) {
    auto var = var_ids.find(node->get_var_id());
    assert(var != var_ids.end());
    value = ValueUse::create(node->get_location(), var->second);
    return;
  }
  sn_assert(false, "dynamic member access not implemented yet");
}

}
}
