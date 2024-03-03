

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

llvm::DIType* LLVMBuilder::get_ditype(types::Type* type) {
  if (type->is_int()) {
    return dbg.builder->createBasicType(type->get_printable_name(), type->as_int()->get_bits(), llvm::dwarf::DW_ATE_signed);
  } else if (type->is_float()) {
    switch (type->as_float()->get_bits()) {
      case 32: return dbg.builder->createBasicType(type->get_printable_name(), 32, llvm::dwarf::DW_ATE_float);
      case 64: return dbg.builder->createBasicType(type->get_printable_name(), 64, llvm::dwarf::DW_ATE_float);
      default: llvm_unreachable("Unknown float width");
    }
  } else if (type->is_void()) {
    return dbg.builder->createUnspecifiedType(type->get_printable_name());
  } else if (auto func = type->as_func()) {
    std::vector<llvm::Metadata*> args = {get_ditype(func->get_return_type())};
    for (auto& param : func->get_param_types()) {
      args.push_back(get_ditype(param));
    }
    auto routine = dbg.builder->createSubroutineType(dbg.builder->getOrCreateTypeArray(args));
    return dbg.builder->createPointerType(routine, 64);
  } else {
    llvm_unreachable("Unknown type");
  }
}

} // namespace backend
} // namespace snowball


