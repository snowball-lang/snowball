
#include "compiler/sil/insts.h"
#include "compiler/sil/binder.h"

namespace snowball {
namespace sil {

void Binder::visit(ast::VarDecl* node) {
  get_type(node);
  assert(false);
}

}
}
