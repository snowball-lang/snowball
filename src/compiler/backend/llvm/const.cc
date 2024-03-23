
#include "compiler/backend/llvm/builder.h"

namespace snowball {
namespace backend {

void LLVMBuilder::emit(const sil::ConstInt* node) {
  value = llvm::ConstantInt::get(get_type(node->get_type()), node->get_value());
}

}
} // namespace snowball
