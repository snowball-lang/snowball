
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
  //   @vtable = { @MotherVtable, @FatherVtable }
  //   
  // This will allow us to extract the corresponding vtable for each interface when needed.
  //
  //  func a(x: Mother) -> will select the @MotherVtable and `x` would contain a tuple.
  //    x = { @MotherVtable, x }
  //
  // Here, we are just returning @vtable's type.
  static std::map<uint64_t, llvm::StructType*> struct_map;
  auto node = type->get_decl();
  if (struct_map.find(node->get_id()) != struct_map.end()) {
    return struct_map[node->get_id()];
  }

  std::vector<llvm::Type*> vtable_types;
  auto has_vtable = node->has_vtable();
  if (!has_vtable) {
    return nullptr;
  }
  // TODO: Do parent vtable if it exists
  auto vtable = llvm::StructType::create(*llvm_ctx.get(), "vtable." + type->get_mangled_name());
  struct_map[node->get_id()] = vtable;
  vtable_types.push_back(builder->getPtrTy()); // Pointer to the vtable
  for (size_t i = 0; i < node->get_implemented_interfaces().size(); i++) {
    vtable_types.push_back(builder->getPtrTy()); // We don't really care about the type of the vtable
  }
  vtable->setBody(vtable_types);
  return vtable;
}

}
} // namespace snowball
