
#include "compiler/utils/utils.h"
#include "compiler/backend/llvm/builder.h"

namespace snowball {
namespace backend {

void LLVMBuilder::emit(const sil::Return* node) {
  auto function = builder->GetInsertBlock()->getParent();
  if (!node->get_value()) {
    value = builder->CreateRetVoid();
    return;
  }
  auto val = node->get_value().value();
  auto llvm_val = expr(val);
  if (val->get_type()->is_class()) {
    auto sret = function->getArg(0);
    builder->CreateStore(llvm_val, sret); // TODO: Memcpy
    value = builder->CreateRetVoid();
  } else {
    value = builder->CreateRet(llvm_val);
  }
}

}
} // namespace snowball
