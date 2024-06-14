
#include "compiler/sil/insts.h"
#include "compiler/sil/binder.h"

namespace snowball {
namespace sil {

void Binder::visit(ast::Return* node) {
  value = Return::create(node->get_location(), get_type(node), accept(node->get_value()));
}

}
}
