
#include "compiler/backend/llvm/builder.h"

namespace snowball {
namespace backend {

void LLVMBuilder::emit(const sil::ValueIndex* node) {
  auto as_class = node->get_value()->get_type()->as_class();
  sn_assert(as_class, "ValueIndex object is not a class");
  auto index = node->get_index(); // TODO: check if we have a virtual table
  auto val = build(node->get_value());
  value = builder->CreateStructGEP(get_type(as_class), val, index);

}

}
} // namespace snowball
