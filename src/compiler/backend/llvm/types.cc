

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
    auto decl = class_type->get_decl();
    auto struct_type = llvm::StructType::create(*llvm_ctx, "class." + type->get_mangled_name());
    builder_cache.struct_map[class_type->get_id()] = struct_type;
    std::vector<llvm::Type*> members;
    if (auto vtable = get_vtable_type(class_type)) {
      members.push_back(vtable->getPointerTo());
    }
    for (auto& member : decl->get_vars()) {
      members.push_back(get_type(member->get_type()));
    }
    struct_type->setBody(members);
    return struct_type;
  } else if (type->is_reference()) {
    return builder->getPtrTy(); // In llvm, references are just pointers
  } else if (type->is_pointer()) {
    return builder->getPtrTy();
  } else {
    llvm_unreachable(("Unsuported llvm type: " + type->get_printable_name()).c_str());
  }
}

llvm::FunctionType* LLVMBuilder::get_func_type(types::FuncType* func_type, bool* has_sret) {
  std::vector<llvm::Type*> param_types;
  func_type->recalibrate_cache();
  for (auto& param : func_type->get_param_types()) {
    param_types.push_back(get_type(param));
  }
  auto ret_type = get_type(func_type->get_return_type());
  if (func_type->get_return_type()->is_class()) {
    if (has_sret != nullptr) *has_sret = true;
    param_types.insert(param_types.begin(), ret_type->getPointerTo());
    ret_type = llvm::Type::getVoidTy(*llvm_ctx);
  }
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
    if (builder_cache.ditype_map.count(class_ty->get_id())) {
      return builder_cache.ditype_map[class_ty->get_id()];
    }
    // TODO: Add virtual table
    auto struct_ty = get_type(type);
    auto layout = builder_ctx.module->getDataLayout().getStructLayout(llvm::cast<llvm::StructType>(struct_ty));
    std::vector<llvm::Metadata*> members;
    auto file = dbg.get_file(class_ty->get_location().file->get_path());
    // TODO: Add members
    auto decl = class_ty->get_decl();
    auto ty = dbg.builder->createClassType(dbg.scope, type->get_printable_name(), file, 0, layout->getSizeInBits(), 
      0, 0, llvm::DINode::DIFlags::FlagZero, nullptr, {});
    if (class_ty->get_decl()->has_vtable()) {
      members.push_back(dbg.builder->createMemberType(
        dbg.scope, "_vptr", file, 0, 64, 0, 0, 
        llvm::DINode::DIFlags::FlagArtificial, 
        dbg.builder->createPointerType(dbg.builder->createUnspecifiedType("vtable"), 64)
      ));
    }
    builder_cache.ditype_map[class_ty->get_id()] = ty;
    for (size_t i = 0; i < decl->get_vars().size(); i++) {
      auto var = decl->get_vars()[i];
      auto var_ty = get_ditype(var->get_type());
      auto loc = var->get_location();
      // TODO: Alignment and offset
      members.push_back(dbg.builder->createMemberType(dbg.scope, var->get_name(), file, loc.line, layout->getElementOffsetInBits(i),0,0, llvm::DINode::DIFlags::FlagZero, var_ty));
    }
    ty->replaceElements(dbg.builder->getOrCreateArray(members));
    return ty;
  } else if (auto ref = type->as_reference()) {
    return dbg.builder->createReferenceType(llvm::dwarf::DW_TAG_reference_type, get_ditype(ref->get_ref()));
  } else if (auto ptr = type->as_pointer()) {
    return dbg.builder->createPointerType(get_ditype(ptr->get_pointee()), 64);
  } else {
    llvm_unreachable(("Unsuported llvm type: " + type->get_printable_name()).c_str());
  }
}

llvm::ArrayType* LLVMBuilder::get_array_type(size_t size, llvm::Type* type) {
  return llvm::ArrayType::get(type, size);
}

} // namespace backend
} // namespace snowball


