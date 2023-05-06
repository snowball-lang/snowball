#include "../../ir/values/Conditional.h"
#include "../../utils/utils.h"
#include "LLVMBuilder.h"

#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>

#define CREATE_CONTINUE(x) \
    if (x || (!builder->GetInsertBlock()->getInstList().back().isTerminator()) || \
        builder->GetInsertBlock()->getInstList().size() == 0) { \
        builder->CreateBr(continueBB); \
    }

namespace snowball {
namespace codegen {

void LLVMBuilder::visit(ir::Conditional *c) {
    auto parent = ctx->getCurrentFunction();
    assert(parent);

    auto trueBB = h.create<llvm::BasicBlock>(*context, "", parent);
    auto falseBB = h.create<llvm::BasicBlock>(*context, "", parent);
    auto continueBB = h.create<llvm::BasicBlock>(*context, "", parent);

    auto cond = build(c->getCondition().get());
    builder->CreateCondBr(cond, trueBB, falseBB);

    builder->SetInsertPoint(trueBB);
    c->getBlock()->visit(this);

    CREATE_CONTINUE(false)

    builder->SetInsertPoint(falseBB);

    if (auto x = c->getElse()) {
        x->visit(this);
    }

    CREATE_CONTINUE((c->getElse() == nullptr))
    builder->SetInsertPoint(continueBB);

}

} // namespace codegen
} // namespace snowball
