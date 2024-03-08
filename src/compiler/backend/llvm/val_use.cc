
#include "compiler/backend/llvm/builder.h"

namespace snowball {
namespace backend {

void LLVMBuilder::emit(const sil::ValueUse* node) {
  auto val = node->get_value();
  if (auto var = val->as<sil::VarDecl>()) {
    value = builder_ctx.get_value(var->get_id());
  } else if (auto fn = val->as<sil::FuncDecl>()) {
    value = builder_ctx.get_value(fn->get_id());
    builder_ctx.dont_load = true;
  } else {
    sn_assert(false, "ValueUse with non-VarDecl value");
  }
}

}
} // namespace snowball
