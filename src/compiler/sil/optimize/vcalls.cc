
#include "compiler/sil/binder.h"

namespace snowball {
namespace sil {

void Binder::optimize_virtual_call(Call*& call) {
  auto callee = call->get_callee();
  auto func_use = callee->as<ValueUse>();
  if (!func_use) return;
  auto func = func_use->get_value()->as<FuncDecl>();
  if (!func || !func->get_virtual()) return;
  auto self_type = func->get_parent_type();
  auto class_type = self_type.has_value() 
    ? self_type.value()->as_class() 
    : nullptr;
  if (!class_type) return;
  auto class_decl = class_type->get_decl();
  if (class_decl->is_interface()) return;
  // TODO: Check if the class has any subclasses (once implemented)
  if (!class_decl->get_final() || class_decl->get_abstract()) return;
  call->set_ignore_virtual(true);
}

}
}
