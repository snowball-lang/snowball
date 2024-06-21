
#include "compiler/backend/llvm/builder.h"

namespace snowball {
namespace backend {

llvm::Value* LLVMBuilder::do_vcall(const sil::Call* node, std::vector<llvm::Value*>& args) {
  auto func = node->get_callee_as_func();
  if (!func) return nullptr;
  if (!(*func)->get_virtual() || node->should_ignore_virtual()) return nullptr;
  // Arg 1 should be the object we are using as the vtable
  sn_assert(false, "Virtual calls are not yet implemented!");
}


}
} // namespace snowball
