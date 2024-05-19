#include <cassert>

#include "compiler/sil/insts.h"
#include "compiler/sil/binder.h"

namespace snowball {
namespace sil {

void Binder::visit(ast::Ident* node) {
  auto var = var_ids.find(node->get_var_id());
  sil::Inst* val = nullptr;
  if (var == var_ids.end() && ctx.current_func) {
    val = ctx.current_func.value()->get_var(node->get_var_id());
  } else {
    val = var->second;
  }
  value = ValueUse::create(node->get_location(), val->get_type(), val);
}

}
}
