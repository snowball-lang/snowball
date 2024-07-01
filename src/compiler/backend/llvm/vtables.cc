
#include "compiler/backend/llvm/builder.h"

namespace snowball {
namespace backend {

llvm::Type* LLVMBuilder::get_vtable_type(types::ClassType* type) {
  // Vtable is a pointer inside the first element of the struct
  // that contains the virtual functions to allow dynamic dispatch.
  // 
  // The way we are going to implement this is by having every implementation's
  // virtual table inside this struct's first element. By doing so, we can simply
  // extract the corresponding virtual table and use it to call the function.
  //
  // e.g. `class Child implements Mother, Father` will have a layout like this:
  // 
  //  { @vtable, ... }
  //   @vtable = { @ChildVtable, @MotherVtable, @FatherVtable }
  //   
  // This will allow us to extract the corresponding vtable for each interface when needed.
  //
  //  func a(x: Mother) -> will select the @MotherVtable and `x` would contain a tuple.
  //    x = { @MotherVtable, x }
  //
  // Here, we are just returning @vtable's type.
  static llvm::DenseMap<uint64_t, llvm::StructType*> struct_map;
  auto node = type->get_decl();
  if (struct_map.find(node->get_id()) != struct_map.end()) {
    return struct_map[node->get_id()];
  }
  
  llvm::SmallVector<llvm::Type*> vtable_types;
  auto has_vtable = node->has_vtable();
  if (!has_vtable) {
    return nullptr;
  }
  // TODO: Do parent vtable if it exists
  size_t vtable_size = 0;
  for (auto& iface : node->get_implemented_interfaces()) {
    auto iface_type = iface.get_internal_type().value()->as_class();
    if (iface_type->get_decl()->has_vtable()) {
      auto count = iface_type->get_decl()->get_virtual_fn_count();
      vtable_size += count;
      vtable_types.push_back(get_array_type(count, builder->getPtrTy()));
    }
  }
  int base_vtable_size = (int)node->get_virtual_fn_count() - vtable_size;
  if (vtable_size < node->get_virtual_fn_count())
    vtable_types.insert(vtable_types.begin(), get_array_type(base_vtable_size, builder->getPtrTy()));
  auto vtable = llvm::StructType::get(*llvm_ctx, vtable_types);
  struct_map[node->get_id()] = vtable;
  return vtable;
}

llvm::Constant* LLVMBuilder::create_vtable_global(types::ClassType* type) {
  if (!type->get_decl()->has_vtable()) {
    return nullptr;
  }
  auto vtable = (llvm::StructType*)get_vtable_type(type);
  sn_assert(vtable, "Vtable type is null");
  auto vtable_name = "vtable." + type->get_mangled_name();
  if (auto existing_vtable = builder_ctx.module->getNamedGlobal(vtable_name)) {
    return existing_vtable;
  }
  auto vtable_global = new llvm::GlobalVariable(*builder_ctx.module.get(), 
    vtable, false, llvm::GlobalValue::InternalLinkage, nullptr, 
    vtable_name);
  if (get_target_triple().isOSBinFormatELF()) {
    vtable_global->setComdat(builder_ctx.module->getOrInsertComdat(vtable_name));
  }
  llvm::SmallVector<llvm::SmallVector<llvm::Constant*>> vtable_init;
  llvm::SmallVector<types::ClassType*> vtabled_types;
  size_t vtable_size = 0;
  for (auto& iface : type->get_decl()->get_implemented_interfaces()) {
    auto decl_type = iface.get_internal_type().value()->as_class();
    if (decl_type->get_decl()->has_vtable()) {
      vtable_size += decl_type->get_decl()->get_virtual_fn_count();
      vtabled_types.push_back(decl_type);
    }
  }
  if (vtable_size < type->get_decl()->get_virtual_fn_count())
    vtabled_types.insert(vtabled_types.begin(), type);
  for (auto& decl_type : vtabled_types) {
    llvm::SmallVector<llvm::Constant*> vtable_entry;
    for (size_t i = 0; i < decl_type->get_decl()->get_virtual_fn_count(); i++) {
      // We are going to replace it anyways
      vtable_entry.push_back(llvm::Constant::getNullValue(builder->getPtrTy()));
    }
    vtable_init.push_back(std::move(vtable_entry));
  }
  for (auto& func_id : type->get_decl()->get_virtual_fn_ids()) {
    auto func_decl = builder_ctx.get_inst(func_id)->as<sil::FuncDecl>();
    auto func_val = llvm::cast<llvm::Constant>(builder_ctx.get_value(func_id));
    // Set the function pointer in the class's vtable
    auto vtable_index = get_vtable_index(func_decl);
    vtable_init[vtable_index.first][vtable_index.second] = func_val;
  }
  std::vector<llvm::Constant*> vtable_entries;
  for (auto& vtable_entry : vtable_init) {
    vtable_entries.push_back(llvm::ConstantArray::get(
      get_array_type(vtable_entry.size(), builder->getPtrTy()), vtable_entry));
  }
  auto vtable_const = llvm::ConstantStruct::get(vtable, vtable_entries);
  vtable_global->setInitializer(vtable_const);
  vtable_global->setAlignment(llvm::Align(8));
  vtable_global->setConstant(true);
  vtable_global->setUnnamedAddr(llvm::GlobalValue::UnnamedAddr::Global);
  vtable_global->setDSOLocal(true);
  return vtable_global;
}

std::pair<unsigned, unsigned> LLVMBuilder::get_vtable_index(const sil::FuncDecl* node) {
  return node->get_vtable_index().value();
}

}
} // namespace snowball
