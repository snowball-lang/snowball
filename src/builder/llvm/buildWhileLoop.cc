#include "../../ir/values/WhileLoop.h"
#include "../../utils/utils.h"
#include "LLVMBuilder.h"

#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>

namespace snowball {
namespace codegen {

void LLVMBuilder::visit(ir::WhileLoop* c) {
  auto parent = ctx->getCurrentFunction();
  assert(parent);
  auto condBB = h.create<llvm::BasicBlock>(*context, "", parent);
  auto whileBB = h.create<llvm::BasicBlock>(*context, "", parent);
  auto continueBB = h.create<llvm::BasicBlock>(*context, "", parent);
  if (c->isDoWhile()) {
    builder->CreateBr(whileBB);
    builder->SetInsertPoint(whileBB);
    c->getBlock()->visit(this);
    if (!builder->GetInsertBlock()->getTerminator()) { builder->CreateBr(condBB); }
    builder->SetInsertPoint(condBB);
    auto cond = build(c->getCondition().get());
    builder->CreateCondBr(cond, whileBB, continueBB);
    builder->SetInsertPoint(continueBB);
  } else {
    builder->CreateBr(condBB);
    builder->SetInsertPoint(condBB);
    auto cond = build(c->getCondition().get());
    builder->CreateCondBr(cond, whileBB, continueBB);
    builder->SetInsertPoint(whileBB);
    c->getBlock()->visit(this);
    if (!builder->GetInsertBlock()->getTerminator()) { builder->CreateBr(condBB); }
    builder->SetInsertPoint(continueBB);
  }
}

} // namespace codegen
} // namespace snowball
