
#include "compiler/sil/insts.h"
#include "compiler/sil/binder.h"

namespace snowball {
namespace sil {

void Binder::visit(ast::ClassDecl* node) {
  auto backup = ctx.ast_current_class;
  ctx.ast_current_class = node;
  for (auto& impl : node->get_implemented_interfaces()) {
    auto type = impl.get_internal_type();
    // Type may not be set in some cases. For example, when the class is generic instanced.
    if (type.has_value())
      // TODO: For now, we are just checking the type is valid, should we do more?
      (void)get_type(type.value(), impl.get_location());
  }
  for (auto& var : node->get_vars()) {
    var->accept(this);
  }
  for (auto& method : node->get_funcs()) {
    method->accept(this);
  }
  ctx.ast_current_class = backup;
}

}
}
