
#include "compiler/sil/insts.h"
#include "compiler/sil/binder.h"

namespace snowball {
namespace sil {

void Binder::visit(ast::MemberAccess* node) {
  sn_assert(false, "MemberAccess not implemented");
}

}
}
