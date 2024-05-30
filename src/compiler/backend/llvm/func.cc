
#include "compiler/backend/llvm/builder.h"

namespace snowball {
namespace backend {

#define IS_EXTERNAL_FN \
  node->get_parent_module()->parent_crate.value() != builder_ctx.parent_crate

void LLVMBuilder::emit(const sil::FuncDecl* node) {
  assert(node->get_type()->is_func());
  auto fn_type = get_func_type(node->get_type()->as_func());  
  if (just_declare) {
    auto linkage = llvm::Function::InternalLinkage;
    if (node->get_external() != frontend::ast::AttributedNode::None
      || node->get_privacy() == frontend::ast::AttributedNode::Public
      || (IS_EXTERNAL_FN)
      || !node->get_body().has_value()) {
      linkage = llvm::Function::ExternalLinkage;
    }
    auto fn = llvm::Function::Create(fn_type, linkage, node->get_mangled_name(), *builder_ctx.module);
    fn->setCallingConv(llvm::CallingConv::C);
    if (node->get_inline())
      fn->addFnAttr(llvm::Attribute::AlwaysInline);
    builder_ctx.set_value(node->get_id(), fn);
  } else if (node->get_external() == frontend::ast::AttributedNode::None) {
    if (IS_EXTERNAL_FN || !node->get_body().has_value()) {
      // We dont want to declare the function multiple times
      // Let's leave it as external
      return;
    }
    auto func = llvm::cast<llvm::Function>(builder_ctx.get_value(node->get_id()));
    auto entry = llvm::BasicBlock::Create(*llvm_ctx, "entry", func);
    builder->SetInsertPoint(entry);
    func->setSubprogram(get_disubprogram(node));
    dbg.scope = func->getSubprogram();
    assert(node->get_params().size() == fn_type->getNumParams());
    builder_ctx.set_current_func(func, node);
    size_t arg_idx = 0;
    for (auto& [id, name] : node->get_params()) {
      auto arg = func->arg_begin();
      std::advance(arg, arg_idx);
      arg->setName(name);
      arg_idx++;
      auto alloc = build(builder_ctx.get_inst(id));
      builder->CreateStore(arg, alloc);
    }
    build(node->get_body().value());
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
