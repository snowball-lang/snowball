
#include "compiler/utils/utils.h"
#include "compiler/backend/llvm/builder.h"

namespace snowball {
namespace backend {

void LLVMBuilder::emit(const sil::Cast* node) {
  auto from = node->get_value()->get_type();
  auto to = node->get_type();
  auto val = expr(node->get_value());
  if (from->is_int() && to->is_int()) {
    auto from_int = from->as_int();
    auto to_int = to->as_int();
    if (from_int->get_bits() < to_int->get_bits()) {
      value = builder->CreateZExt(val, get_type(to));
    } else if (from_int->get_bits() > to_int->get_bits()) {
      value = builder->CreateTrunc(val, get_type(to));
    }
  } else if (from->is_int() && to->is_float()) {
    value = builder->CreateSIToFP(val, get_type(to));
  } else if (from->is_float() && to->is_int()) {
    value = builder->CreateFPToSI(val, get_type(to));
  } else if (from->is_float() && to->is_float()) {
    value = builder->CreateFPCast(val, get_type(to));
  } else if (from->is_pointer() && to->is_pointer()) {
    value = builder->CreateBitCast(val, get_type(to));
  } else {
    sn_unreachable();
  }
}

}
} // namespace snowball
