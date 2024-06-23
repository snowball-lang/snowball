
#include "compiler/backend/llvm/builder.h"

namespace snowball {
namespace backend {

void LLVMBuilder::emit(const sil::Call* node) {
  std::vector<llvm::Value*> args;
  args.reserve(node->get_args().size());
  bool is_ctor = false;
  if (auto func = node->get_callee_as_func()) {
    if (func.value()->is_constructor()) {
      is_ctor = true;
      args.push_back(alloc(func.value()->get_parent_type().value(), ".this"));
    }
  }
  for (auto& arg : node->get_args()) {
    args.push_back(expr(arg));
  }
  if (auto val = do_vcall(node, args)) {
    value = val;
    return;
  }
  auto callee = expr(node->get_callee());
  set_debug_info(node);
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
  set_debug_info(node);
  value = builder->CreateCall(callee_type, callee, args); 
  if (has_sret) {
    value = sret;
  } else if (is_ctor) {
    value = args[0];
  }
}

}
} // namespace snowball
