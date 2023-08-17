
#include "../../ast/types/ReferenceType.h"
#include "../../ir/values/Call.h"
#include "../../ir/values/IndexExtract.h"
#include "../../ir/values/Return.h"
#include "../../utils/utils.h"
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
      auto retArg = ctx->getCurrentFunction()->getArg(0);
      if (llvm::isa<llvm::LoadInst>(expr)) { expr = llvm::cast<llvm::LoadInst>(expr)->getOperand(0); }

      if (utils::dyn_cast<ir::IndexExtract>(exprValue)) {
        builder->CreateMemCpy(retArg, llvm::MaybeAlign(), expr, llvm::MaybeAlign(),
                              module->getDataLayout().getTypeAllocSize(getLLVMType(ret->getType())), 0);
      } else {
        expr->replaceAllUsesWith(retArg);
      }

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
