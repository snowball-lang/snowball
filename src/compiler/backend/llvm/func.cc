
#include "compiler/backend/llvm/builder.h"

namespace snowball {
namespace backend {

#define IS_EXTERNAL_FN \
  node->get_parent_module()->parent_crate.value() != builder_ctx.parent_crate

void LLVMBuilder::emit(const sil::FuncDecl* node) {
  assert(node->get_type()->is_func());
  bool has_sret = false;
  auto fn_type = get_func_type(node->get_type()->as_func(), &has_sret);
  if (just_declare) {
    auto linkage = llvm::Function::InternalLinkage;
    bool is_external = IS_EXTERNAL_FN;
    if (is_external && node->get_privacy() == frontend::ast::AttributedNode::Private) {
      // We dont want to declare the function multiple times
      // If it's not on the same module and it's private
      // we are 99.99% sure it's not going to be used outside
      return;
    }
    if (node->get_external() != frontend::ast::AttributedNode::None
      || node->get_privacy() == frontend::ast::AttributedNode::Public
      || is_external
      || !node->get_body().has_value()) {
      linkage = llvm::Function::ExternalLinkage;
    }
    auto fn = llvm::Function::Create(fn_type, linkage, node->get_mangled_name(), *builder_ctx.module);
    fn->setCallingConv(llvm::CallingConv::C);
    if (node->get_inline())
      fn->addFnAttr(llvm::Attribute::AlwaysInline);
    if (has_sret) {
      auto& arg = *fn->arg_begin();
      auto attr_builder = llvm::AttrBuilder(*llvm_ctx);
      attr_builder.addStructRetAttr(get_type(node->get_type()->as_func()->get_return_type()));
      attr_builder.addAttribute(llvm::Attribute::NoAlias);
      attr_builder.addAttribute(llvm::Attribute::NoUndef);
      attr_builder.addAttribute(llvm::Attribute::NonNull);
      arg.setName("sret");
      arg.addAttrs(attr_builder);
    }
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
    assert(node->get_params().size() == fn_type->getNumParams() - has_sret);
    builder_ctx.set_current_func(func, node);
    if (node->is_constructor()) {
      generate_constructor(node);
    }
    size_t arg_idx = 0;
    for (auto& [id, name] : node->get_params()) {
      auto arg = func->arg_begin();
      std::advance(arg, arg_idx + has_sret);
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

void LLVMBuilder::generate_constructor(const sil::FuncDecl* node) {
  auto parent_type = node->get_parent_type().value()->as_class();
  auto vtable_type = get_vtable_type(parent_type);
  if (vtable_type == nullptr) return;
  debug(F("[func] Generating constructor for class {}", node->get_parent_type().value()->get_printable_name()));
  auto ctor = llvm::BasicBlock::Create(*llvm_ctx, "ctor", builder_ctx.get_current_func());
  auto cont = llvm::BasicBlock::Create(*llvm_ctx, "ctor.cont", builder_ctx.get_current_func());
  builder->CreateBr(ctor);
  builder->SetInsertPoint(ctor);
  auto vtable_global = create_vtable_global(parent_type);
  auto vtable_storage = builder->CreateStructGEP(get_type(parent_type), builder_ctx.get_current_func()->arg_begin(), 0);
  builder->CreateStore(vtable_global, vtable_storage);
  builder->CreateBr(cont);
  builder->SetInsertPoint(cont);
}

}
} // namespace snowball
