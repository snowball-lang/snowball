
#include "compiler/backend/llvm/builder.h"

namespace snowball {
namespace backend {

void LLVMBuilder::emit(const sil::Call* node) {
  std::vector<llvm::Value*> args;
  args.reserve(node->get_args().size());
  for (auto& arg : node->get_args()) {
    args.push_back(expr(arg));
  }
  auto callee = expr(node->get_callee());
  set_debug_info(node);
  auto fn_type = node->get_callee()->get_type()->as_func();
  assert(fn_type != nullptr);
  value = builder->CreateCall(get_func_type(fn_type), callee, args); 
}

}
} // namespace snowball
