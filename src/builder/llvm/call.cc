
#include "../../ir/values/WhileLoop.h"
#include "../../utils/utils.h"
#include "LLVMBuilder.h"

#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>

namespace snowball {
namespace codegen {

llvm::Value* LLVMBuilder::createCall(llvm::FunctionType* ty, llvm::Value* callee, llvm::ArrayRef<llvm::Value*> args) {
  if (tryCatchStack.empty()) {
    return builder->CreateCall(ty, callee, args);
  } else {
    auto normalBlock = llvm::BasicBlock::Create(*context, "invoke.normal", ctx->getCurrentFunction());
    auto unwindBlock = tryCatchStack.back().catchBlock;
    auto result = builder->CreateInvoke(ty, callee, normalBlock, unwindBlock, args);
    builder->SetInsertPoint(normalBlock);
    return result;
  }
}

} // namespace codegen
} // namespace snowball
