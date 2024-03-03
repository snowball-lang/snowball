
#include "compiler/backend/llvm/builder.h"

namespace snowball {
namespace backend {

void LLVMBuilder::emit(const sil::VarDecl* node) {
  auto alloca = alloc(node->get_type(), "__var." + node->get_name());
  if (node->get_value()) {
    auto value = expr(node->get_value().value());
    builder->CreateStore(value, alloca);
  }
  builder_ctx.set_value(node->get_id(), alloca);
}

}
} // namespace snowball
