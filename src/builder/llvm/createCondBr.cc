
#include "../../ir/values/WhileLoop.h"
#include "../../utils/utils.h"
#include "LLVMBuilder.h"
#include "../../ir/values/EnumInit.h"
#include "../../ir/values/Call.h"

#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>

namespace snowball {
namespace codegen {

void LLVMBuilder::createCondBr(llvm::Value* cond, llvm::BasicBlock* thenBlock, llvm::BasicBlock* elseBlock) {
  if (cond->getType()->isIntegerTy(8)) {
    cond = builder->CreateTrunc(cond, builder->getInt1Ty());
  }
  builder->CreateCondBr(cond, thenBlock, elseBlock);
}

} // namespace codegen
} // namespace snowball
