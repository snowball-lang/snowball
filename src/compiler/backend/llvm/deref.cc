
#include "compiler/utils/utils.h"
#include "compiler/backend/llvm/builder.h"

namespace snowball {
namespace backend {

void LLVMBuilder::emit(const sil::Dereference* node) {
  auto val = node->get_value();
  auto llvm_val = build(val);
  value = builder->CreateLoad(get_type(val->get_type()), llvm_val);
}

}
} // namespace snowball
