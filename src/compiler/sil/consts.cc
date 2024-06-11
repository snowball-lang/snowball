
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

void Binder::visit(ast::String* node) {
  auto val = node->get_value();
  // Remove the parsed quotes form the value
  val = val.substr(1, val.size() - 2);
  if (node->get_prefix() == 'c' || node->get_prefix() == 'C') {
    value = ConstString::create(node->get_location(), get_type(node), val);
    return;
  }
  sn_assert(false, "Normal strings are not supported yet!");
}

}
}
