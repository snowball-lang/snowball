
#include "../../ast/errors/error.h"
#include "../../ir/values/Argument.h"
#include "../../utils/utils.h"
#include "LLVMBuilder.h"

#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>
#include <llvm/IR/Verifier.h>

using namespace snowball::utils;

namespace snowball {
namespace codegen {

llvm::Value* LLVMBuilder::createInsertValue(llvm::Value* v, llvm::Value* rhs, types::Type* refType) {
  while (llvm::isa<llvm::LoadInst>(rhs)) {
    auto l = llvm::cast<llvm::LoadInst>(rhs);
    rhs = l->getOperand(0);
    //l->eraseFromParent();
  }
  // auto lhs = builder->CreateExtractValue(leftValue, i);
  // llvm::Value* load = builder->CreateLoad(getLLVMType(refType), lhs);
  // auto load = builder->CreateInsertValue(v, v, i);
  if (auto x = utils::cast<types::ReferenceType>(refType); x && utils::cast<types::NumericType>(x->getBaseType()) && llvm::isa<llvm::LoadInst>(v)) {
    auto l = llvm::cast<llvm::LoadInst>(v);
    v = l->getOperand(0);
    //l->eraseFromParent();
  }

  return builder->CreateStore(v, rhs);
}

} // namespace codegen
} // namespace snowball
