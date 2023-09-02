
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

    // case: "let a = x();" where x is a function returning a type that's not a pointer
    // We store the value into the first argument of the function.
    // This is because we can't return a struct that's not a pointer.
    // read more here: https://discourse.llvm.org/t/c-returning-struct-by-value/40518
    if (utils::cast<types::DefinedType>(ret->getType())) {
      auto retArg = ctx->getCurrentFunction()->getArg(0);
      auto store = builder->CreateStore(expr, retArg);

      builder->CreateRetVoid();
      return;
    }

    if (utils::cast<types::PointerType>(ret->getType()) && llvm::isa<llvm::LoadInst>(expr)) {
      val = llvm::cast<llvm::LoadInst>(expr)->getPointerOperand();
    }

    val = builder->CreateRet(expr);
  } else {
    val = builder->CreateRetVoid();
  }

  this->value = val;
}

} // namespace codegen
} // namespace snowball
