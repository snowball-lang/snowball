
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
    auto e = build(exprValue.get());
    auto funcRet = ctx->getCurrentFunction()->getReturnType();

    // case: "let a = x();" where x is a function returning a type that's not a pointer
    // We store the value into the first argument of the function.
    // This is because we can't return a struct that's not a pointer.
    // read more here: https://discourse.llvm.org/t/c-returning-struct-by-value/40518
    if (utils::cast<types::DefinedType>(ret->getType())) {
      auto retArg = ctx->getCurrentFunction()->getArg(0);

      if (llvm::isa<llvm::LoadInst>(e)) {
        e = llvm::cast<llvm::LoadInst>(e)->getPointerOperand();
      }

      builder->CreateMemCpy(retArg, llvm::MaybeAlign(), e, llvm::MaybeAlign(), builder->getInt32(module->getDataLayout().getTypeAllocSize(getLLVMType(ret->getType()))), 0);
      //auto store = builder->CreateStore(load(e, ret->getType()), retArg);

      builder->CreateRetVoid();
      return;
    }

    if ((is<types::PointerType>(ret->getType()) || is<types::ReferenceType>(ret->getType())) && llvm::isa<llvm::LoadInst>(e)) {
      e = llvm::cast<llvm::LoadInst>(e)->getPointerOperand();
    }

    val = builder->CreateRet(e);
  } else {
    val = builder->CreateRetVoid();
  }

  this->value = val;
}

} // namespace codegen
} // namespace snowball
