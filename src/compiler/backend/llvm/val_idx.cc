
#include "compiler/backend/llvm/builder.h"

namespace snowball {
namespace backend {

void LLVMBuilder::emit(const sil::ValueIndex* node) {
  auto as_class = node->get_value()->get_type()->as_class();
  if (auto as_ref = node->get_value()->get_type()->as_reference();
      as_ref && !as_class) {
    as_class = as_ref->get_ref()->as_class();
  }
  sn_assert(as_class, "ValueIndex object is not a class");
  auto index = node->get_index() + as_class->get_decl()->has_vtable();
  auto val = expr(node->get_value());
  if (val->getType()->isStructTy()) {
    val = llvm::cast<llvm::LoadInst>(val)->getPointerOperand();
  }
  value = builder->CreateStructGEP(get_type(as_class), val, index, "val_idx");
}

}
} // namespace snowball
