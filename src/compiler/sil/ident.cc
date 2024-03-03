#include <cassert>

#include "compiler/sil/insts.h"
#include "compiler/sil/binder.h"

namespace snowball {
namespace sil {

void Binder::visit(ast::Ident* node) {
  auto var = var_ids.find(node->get_var_id());
  assert(var != var_ids.end());
  value = ValueUse::create(node->get_location(), var->second);
}

}
}
