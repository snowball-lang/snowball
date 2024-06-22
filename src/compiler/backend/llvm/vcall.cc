
#include "compiler/backend/llvm/builder.h"

namespace snowball {
namespace backend {

llvm::Value* LLVMBuilder::do_vcall(const sil::Call* node, std::vector<llvm::Value*>& args) {
  auto func = node->get_callee_as_func();
  if (!func) return nullptr;
  if (!(*func)->get_virtual() || node->should_ignore_virtual()) return nullptr;
  // Arg 1 should be the object we are using as the vtable
  auto func_val = func.value();
  if (func_val->get_parent_type().has_value()) {
    auto self_type = func_val->get_parent_type().value();
    auto class_type = self_type->as_class();
    if (class_type->is_interface_decl()) {
      sn_assert(false, "Virtual calls are not yet implemented!");
    } else {
      auto vtable_load = builder->CreateStructGEP(
        get_type(class_type),
        args[0],
        0
      );
      auto [vtable, index] = get_vtable_index(func_val);
      auto vtable_ptr = builder->CreateLoad(builder->getPtrTy(), vtable_load);
      auto func_table_ptr = builder->CreateGEP(
        get_vtable_type(class_type),
        vtable_ptr,
        {builder->getInt64(vtable)}
      );
      auto func_ptr = builder->CreateGEP(
        ((llvm::StructType*)get_vtable_type(class_type))->getElementType(vtable),
        func_table_ptr,
        {builder->getInt64(index)}
      );
      auto func_load = builder->CreateLoad(builder->getPtrTy(), func_ptr);
      return builder->CreateCall(get_func_type(func_val->get_type()->as_func()), func_load, args);
    }
  }
  return nullptr;
}


}
} // namespace snowball
