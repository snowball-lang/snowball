
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

using namespace utils;

void LLVMBuilder::visit(ir::Return* ret) {
  auto exprValue = ret->getExpr();

  llvm::Value* val = nullptr;
  if (exprValue != nullptr) {
    auto funcRet = ctx->getCurrentFunction()->getReturnType();

    // case: "let a = x();" where x is a function returning a type that's not a pointer
    // We store the value into the first argument of the function.
    // This is because we can't return a struct that's not a pointer.
    // read more here: https://discourse.llvm.org/t/c-returning-struct-by-value/40518
    if (utils::cast<types::DefinedType>(ret->getType())) {
      auto retArg = ctx->getCurrentFunction()->getArg(0);
      bool doNotMove = false;
      if (is<ir::Call>(exprValue.get()) && !is<ir::ObjectInitialization>(exprValue.get()) &&
          !is<ir::ObjectInitialization>(exprValue.get())) {
        ctx->retValueUsedFromArg = true;
        doNotMove = true;
      }

      auto e = build(exprValue.get());
      ctx->retValueUsedFromArg = false;

      auto sretBB = llvm::BasicBlock::Create(*context, "sret", ctx->getCurrentFunction());
      builder->CreateBr(sretBB);
      builder->SetInsertPoint(sretBB);

      if (llvm::isa<llvm::LoadInst>(e)) { e = llvm::cast<llvm::LoadInst>(e)->getPointerOperand(); }

      if (!doNotMove) {
        builder->CreateMemCpy(
                retArg, llvm::MaybeAlign(), e, llvm::MaybeAlign(), builder->getInt64(ret->getType()->sizeOf()), 0
        );
      }
      // auto store = builder->CreateStore(load(e, ret->getType()), retArg);

      builder->CreateRetVoid();
      return;
    }
    auto e = expr(exprValue.get());
    val = builder->CreateRet(e);
  } else {
    val = builder->CreateRetVoid();
  }

  this->value = val;
}

} // namespace codegen
} // namespace snowball
