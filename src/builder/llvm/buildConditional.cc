#include "../../ir/values/Conditional.h"
#include "../../utils/utils.h"
#include "LLVMBuilder.h"

#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>

#define CREATE_CONTINUE(x) \
  if (x || !builder->GetInsertBlock()->getTerminator()) { builder->CreateBr(continueBB); }

namespace snowball {
namespace codegen {

void LLVMBuilder::visit(ir::Conditional* c) {
  auto parent = ctx->getCurrentFunction();
  assert(parent);
  auto trueBB = h.create<llvm::BasicBlock>(*context, "cond.then", parent);
  auto falseBB = h.create<llvm::BasicBlock>(*context, "cond.else", parent);
  auto continueBB = h.create<llvm::BasicBlock>(*context, "cond.cont", parent);
  auto cond = expr(c->getCondition().get());
  createCondBr(cond, trueBB, falseBB);
  builder->SetInsertPoint(trueBB);
  build(c->getBlock().get());
  CREATE_CONTINUE(false)
  builder->SetInsertPoint(falseBB);
  if (auto x = c->getElse()) { build(x.get()); }
  CREATE_CONTINUE((c->getElse() == nullptr))
  builder->SetInsertPoint(continueBB);
}

} // namespace codegen
} // namespace snowball
