
#include "compiler/sil/insts.h"
#include "compiler/sil/binder.h"

namespace snowball {
namespace sil {

void Binder::visit(ast::ClassDecl* node) {
  auto backup = ctx.ast_current_class;
  ctx.ast_current_class = node;
  for (auto& method : node->get_funcs()) {
    method->accept(this);
  }
  ctx.ast_current_class = backup;
}

}
}
