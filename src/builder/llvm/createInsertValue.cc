
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
    llvm::Value* leftValue = llvm::cast<llvm::ExtractValueInst>(rhs)
        ->getAggregateOperand();;
    auto vload = llvm::cast<llvm::LoadInst>(leftValue)->getPointerOperand();

    //auto lhs = builder->CreateExtractValue(leftValue, i);
    //llvm::Value* load = builder->CreateLoad(getLLVMType(refType), lhs);
    auto load = builder->CreateInsertValue(leftValue, v, i);
    return builder->CreateStore(load, vload);
}

} // namespace codegen
} // namespace snowball
