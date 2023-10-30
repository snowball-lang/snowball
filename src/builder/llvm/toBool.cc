
#include "../../ast/errors/error.h"
#include "../../utils/utils.h"
#include "LLVMBuilder.h"

#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>
#include <memory>

using namespace snowball::utils;

namespace snowball {
namespace codegen {

llvm::Value* LLVMBuilder::toBool(llvm::Value* v, bool isSigned) {
    if (v->getType()->isIntegerTy()) {
        if (v->getType()->getIntegerBitWidth() == 1) return v;
        return builder->CreateICmpNE(v, llvm::ConstantInt::get(v->getType(), 0, isSigned));
    } else if (v->getType()->isFloatingPointTy()) {
        return builder->CreateFCmpONE(v, llvm::ConstantFP::get(v->getType(), 0));
    } else if (v->getType()->isPointerTy()) {
        return builder->CreateICmpNE(v, llvm::ConstantPointerNull::get(llvm::cast<llvm::PointerType>(v->getType())));
    }
    
    Syntax::E<BUG>("Unknown value type! Cannot convert to bool!");
    assert(false);
}

} // namespace codegen
} // namespace snowball
