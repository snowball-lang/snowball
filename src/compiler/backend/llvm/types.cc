

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
  } else if (type->is_class()) {
    auto class_type = type->as_class();
    if (builder_cache.struct_map.count(class_type->get_id())) {
      return builder_cache.struct_map[class_type->get_id()];
    }
    // TODO: Create also the virtual table
    auto struct_type = llvm::StructType::create(*llvm_ctx, type->get_mangled_name());
    builder_cache.struct_map[class_type->get_id()] = struct_type;
    std::vector<llvm::Type*> members;
    //for (auto& member : class_type->get_members()) {
    //  members.push_back(get_type(member));
    //}
    struct_type->setBody(members);
    return struct_type;
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
  } else if (auto class_ty = type->as_class()) {
    // TODO: Add virtual table
    auto struct_ty = get_type(type);
    auto layout = builder_ctx.module->getDataLayout().getStructLayout(llvm::cast<llvm::StructType>(struct_ty));
    std::vector<llvm::Metadata*> members;
    auto file = dbg.get_file(class_ty->get_location().file->get_path());
    // TODO: Add members
    //for (unsigned i = 0; i < struct_ty->getStructNumElements(); i++) {
    //  auto member = dbg.builder->createMemberType("", file, 0, layout->getElementOffsetInBits(i), get_ditype(class_ty->get_members()[i]));
    //  members.push_back(member);
    //}
    return dbg.builder->createStructType(dbg.scope, type->get_printable_name(), file, 0, layout->getSizeInBits(), 0 /* TODO: Aligment! */, llvm::DINode::DIFlags::FlagZero, nullptr, dbg.builder->getOrCreateArray(members));
  } else {
    llvm_unreachable("Unknown type");
  }
}

} // namespace backend
} // namespace snowball


