
#include "compiler/backend/llvm/builder.h"

namespace snowball {
namespace backend {

void LLVMBuilder::emit(const sil::ValueUse* node) {
  auto val = node->get_value();
  if (auto var = val->as<sil::VarDecl>()) {
    value = builder_ctx.get_value(var->get_id());
  } else {
    sn_assert(false, "ValueUse with non-VarDecl value");
  }
}

}
} // namespace snowball
