
#include "compiler/backend/llvm/builder.h"

namespace snowball {
namespace backend {

void LLVMBuilder::emit(const sil::FuncDecl* node) {
  if (just_declare) {
    assert(node->get_type()->is_func());
    auto fn_type = get_func_type(node->get_type()->as_func());
    auto fn = llvm::Function::Create(fn_type, llvm::Function::InternalLinkage, node->get_name(), *builder_ctx.module);
    builder_ctx.set_func(node->get_id(), fn);
  } else {
    auto func = builder_ctx.get_func(node->get_id());
    if (node->get_external() == frontend::ast::AttributedNode::None) {
      auto entry = llvm::BasicBlock::Create(*llvm_ctx, "entry", func);
      builder->SetInsertPoint(entry);
      for (auto& param : func->args()) {
        auto alloca = builder->CreateAlloca(param.getType(), nullptr, param.getName());
        builder->CreateStore(&param, alloca);
        //builder_ctx.set_value(node->get_id(param.getName()), alloca);
      }
    }
  }
}

}
} // namespace snowball
