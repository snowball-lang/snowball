
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
  if (auto val = do_vcall(node, callee, args)) {
    value = val;
    return;
  }
  auto fn_type = node->get_callee()->get_type()->as_func();
  assert(fn_type != nullptr);
  bool has_sret = false;
  auto callee_type = get_func_type(fn_type, &has_sret);
  llvm::Value* sret = nullptr;
  if (has_sret) {
    // Maybe we can use a single alloca for all sret values?
    sret = alloc(fn_type->get_return_type(), ".call-sret");
    args.insert(args.begin(), sret);
  }
  value = builder->CreateCall(callee_type, callee, args); 
  if (has_sret) {
    value = sret;
  }
}

}
} // namespace snowball
