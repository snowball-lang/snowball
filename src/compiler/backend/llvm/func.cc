
#include "compiler/backend/llvm/builder.h"

namespace snowball {
namespace backend {

void LLVMBuilder::emit(const sil::FuncDecl* node) {
  assert(node->get_type()->is_func());
  auto fn_type = get_func_type(node->get_type()->as_func());  
  if (just_declare) {
    auto linkage = llvm::Function::InternalLinkage;
    if (node->get_external() != frontend::ast::AttributedNode::None) {
      linkage = llvm::Function::ExternalLinkage;
    }
    auto fn = llvm::Function::Create(fn_type, linkage, node->get_name(), *builder_ctx.module);
    fn->setCallingConv(llvm::CallingConv::C);
    if (node->get_inline())
      fn->addFnAttr(llvm::Attribute::AlwaysInline);
    builder_ctx.set_func(node->get_id(), fn);
  } else if (node->get_external() == frontend::ast::AttributedNode::None) {
    auto func = builder_ctx.get_func(node->get_id());
    auto entry = llvm::BasicBlock::Create(*llvm_ctx, "entry", func);
    builder->SetInsertPoint(entry);
    for (auto& param : func->args()) {
      auto alloca = builder->CreateAlloca(param.getType(), nullptr, param.getName());
      builder->CreateStore(&param, alloca);
      //builder_ctx.set_value(node->get_id(param.getName()), alloca);
    }
    if (builder->GetInsertBlock()->empty() || !builder->GetInsertBlock()->back().isTerminator()) {
      if (fn_type->getReturnType()->isVoidTy()) {
        builder->CreateRetVoid();
      } else {
        builder->CreateRet(llvm::Constant::getNullValue(fn_type->getReturnType()));
      }
    }
  }
}

}
} // namespace snowball
