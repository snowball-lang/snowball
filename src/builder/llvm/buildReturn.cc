
#include "../../ir/values/Call.h"
#include "../../ir/values/Return.h"
#include "../../utils/utils.h"
#include "../../ast/types/ReferenceType.h"
#include "LLVMBuilder.h"

#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>

namespace snowball {
namespace codegen {

void LLVMBuilder::visit(ir::Return* ret) {
  auto exprValue = ret->getExpr();

  llvm::Value* val = nullptr;
  if (exprValue != nullptr) {
    auto expr = build(exprValue.get());
    auto funcRet = ctx->getCurrentFunction()->getReturnType();
    // case: "return x();" where x is a function returning a type that's not a pointer
    if (utils::cast<types::DefinedType>(ret->getType())) {
      //expr = builder->CreateLoad(getLLVMType(exprValue->getType()), expr);
      //auto retArg = ctx->getCurrentFunction()->getArg(0);
      //auto alloca = createAlloca(getLLVMType(ret->getType()));
      //auto size = module->getDataLayout().getTypeAllocSize(getLLVMType(ret->getType()));
//
      //builder->CreateLifetimeStart(alloca, builder->getInt64(size));
      //builder->CreateStore(expr, alloca);
      //
      //builder->CreateMemCpy(alloca, llvm::MaybeAlign(), retArg, llvm::MaybeAlign(),
      //  module->getDataLayout().getTypeAllocSize(getLLVMType(ret->getType())), 0);
      //builder->CreateLifetimeEnd(alloca, builder->getInt64(size));

      if (llvm::isa<llvm::LoadInst>(expr)) {
        expr = llvm::cast<llvm::LoadInst>(expr)->getOperand(0);
      }

      auto retArg = ctx->getCurrentFunction()->getArg(0);
      expr->replaceAllUsesWith(retArg);

      builder->CreateRetVoid();
      return;
    }

    val = builder->CreateRet(expr);
  } else {
    val = builder->CreateRetVoid();
  }

  this->value = val;
}

} // namespace codegen
} // namespace snowball
