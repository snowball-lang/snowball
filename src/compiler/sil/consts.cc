
#include "compiler/sil/insts.h"
#include "compiler/sil/binder.h"

namespace snowball {
namespace sil {

void Binder::visit(ast::Number* node) {
  auto number = node->get_value();
  assert(number.size() > 0);
  int64_t int_val = std::stoull(number);
  value = ConstInt::create(node->get_location(), get_type(node), int_val);
}

}
}
