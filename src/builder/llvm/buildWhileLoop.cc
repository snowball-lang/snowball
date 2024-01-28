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

  auto backupLoop = ctx->loop;
  ctx->loop = {
    .continueBlock = condBB,
    .breakBlock = continueBB,
  };

  if (c->isDoWhile()) {
    builder->CreateBr(whileBB);
    builder->SetInsertPoint(whileBB);
    (void) build(c->getBlock().get());
    if (!builder->GetInsertBlock()->getTerminator()) { builder->CreateBr(condBB); }
    builder->SetInsertPoint(condBB);
    auto cond = expr(c->getCondition().get());
    createCondBr(cond, whileBB, continueBB);
    builder->SetInsertPoint(continueBB);
  } else {
    if (auto x = c->getForCond()) {
      // Using "continue" must execute the for condition
      // before jumping to the next iteration
      // "x" is `for i; i < 10; i++ {}`
      //                        ^^^ <- this
      auto forCondBB = h.create<llvm::BasicBlock>(*context, "for.cond", parent);
      
      builder->CreateBr(condBB);
      builder->SetInsertPoint(condBB);
      auto cond = expr(c->getCondition().get());
      ctx->loop.continueBlock = forCondBB;
      
      createCondBr(cond, whileBB, continueBB);
      builder->SetInsertPoint(whileBB);
      (void) build(c->getBlock().get());

      if (!builder->GetInsertBlock()->getTerminator()) { builder->CreateBr(forCondBB); }
      builder->SetInsertPoint(forCondBB);

      (void)build(x.get());
      builder->CreateBr(condBB);
      builder->SetInsertPoint(continueBB);
    } else {
      builder->CreateBr(condBB);
      builder->SetInsertPoint(condBB);
      auto cond = expr(c->getCondition().get());
      createCondBr(cond, whileBB, continueBB);
      builder->SetInsertPoint(whileBB);
      (void) build(c->getBlock().get());
      if (!builder->GetInsertBlock()->getTerminator()) { builder->CreateBr(condBB); }
      builder->SetInsertPoint(continueBB);
    }
  }

  ctx->loop = backupLoop;
}

} // namespace codegen
} // namespace snowball
