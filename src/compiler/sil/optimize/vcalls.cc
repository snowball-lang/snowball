
#include "compiler/sil/binder.h"

namespace snowball {
namespace sil {

void Binder::optimize_virtual_call(Call*& call) {
  auto func = call->get_callee_as_func();
  if (!func.has_value() && !func.value()->get_virtual()) return;
  auto self_type = func.value()->get_parent_type();
  auto class_type = self_type.has_value() 
    ? self_type.value()->as_class() 
    : nullptr;
  if (!class_type) return;
  auto class_decl = class_type->get_decl();
  if (class_decl->is_interface()) return;
  // TODO: Check if the class has any subclasses (once implemented)
  // If it's final, we can directly optimize the call
  if (class_decl->get_abstract() || !class_decl->get_final()) return;
  call->set_ignore_virtual(true);
}

}
}
