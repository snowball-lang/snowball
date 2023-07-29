
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

llvm::Value* LLVMBuilder::createInsertValue(llvm::Value* v, uint32_t i, llvm::Value* rhs, types::Type* refType) {
  if (llvm::isa<llvm::LoadInst>(rhs)) {
    auto l = llvm::cast<llvm::LoadInst>(rhs);
    rhs = l->getOperand(0);
  }
  // auto lhs = builder->CreateExtractValue(leftValue, i);
  // llvm::Value* load = builder->CreateLoad(getLLVMType(refType), lhs);
  // auto load = builder->CreateInsertValue(v, v, i);
  return builder->CreateStore(v, rhs);
}

} // namespace codegen
} // namespace snowball
