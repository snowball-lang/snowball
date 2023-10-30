#include "../../ir/values/LoopFlow.h"
#include "../../utils/utils.h"
#include "LLVMBuilder.h"

#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>

namespace snowball {
namespace codegen {

void LLVMBuilder::visit(ir::LoopFlow* c) {
  switch (c->getFlowType()) {
    case ir::LoopFlowType::Break:
      builder->CreateBr(ctx->loop.breakBlock);
      break;
    case ir::LoopFlowType::Continue:
      builder->CreateBr(ctx->loop.continueBlock);
      break;
    default:
      assert(false);
  }
}

} // namespace codegen
} // namespace snowball
