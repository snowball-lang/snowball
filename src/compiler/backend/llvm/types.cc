

#include "compiler/backend/llvm/builder.h"

namespace snowball {
namespace backend {

llvm::Type* LLVMBuilder::get_type(types::Type* type) {
  if (type->is_int()) {
    return llvm::Type::getIntNTy(*llvm_ctx, type->as_int()->get_bits());
  } else if (type->is_float()) {
    switch (type->as_float()->get_bits()) {
      case 32: return llvm::Type::getFloatTy(*llvm_ctx);
      case 64: return llvm::Type::getDoubleTy(*llvm_ctx);
      default: llvm_unreachable("Unknown float width");
    }
  } else if (type->is_void()) {
    return llvm::Type::getVoidTy(*llvm_ctx);
  } else if (type->is_func()) {
    return get_func_type(type->as_func())->getPointerTo();
  } else {
    llvm_unreachable("Unknown type");
  }
}

llvm::FunctionType* LLVMBuilder::get_func_type(types::FuncType* func_type) {
  std::vector<llvm::Type*> param_types;
  for (auto& param : func_type->get_param_types()) {
    param_types.push_back(get_type(param));
  }
  auto ret_type = get_type(func_type->get_return_type());
  return llvm::FunctionType::get(ret_type, param_types, false);
}

} // namespace backend
} // namespace snowball


