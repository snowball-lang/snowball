
#include "../../ast/errors/error.h"
#include "../../utils/utils.h"
#include "LLVMBuilder.h"

#include <llvm-14/llvm/IR/DerivedTypes.h>
#include <llvm-14/llvm/IR/Type.h>
#include <llvm-14/llvm/IR/Value.h>
#include <memory>

using namespace snowball::utils;

namespace snowball {
namespace codegen {

ptr<llvm::Type> LLVMBuilder::getLLVMType(std::shared_ptr<types::Type> t) {
    return getLLVMType(t.get());
}

ptr<llvm::Type> LLVMBuilder::getLLVMType(ptr<types::Type> t) {
    if (cast<types::Int64Type>(t)) {
        return builder->getInt64Ty();
    } else if (cast<types::Int32Type>(t)) {
        return builder->getInt32Ty();
    } else if (cast<types::Int16Type>(t)) {
        return builder->getInt16Ty();
    } else if (cast<types::Int8Type>(t)) {
        return builder->getInt8Ty();
    } else if (cast<types::StringType>(t)) {
        return builder->getInt8PtrTy();
    } else if (cast<types::CObjectType>(t)) {
        return builder->getInt8PtrTy();
    } else if (cast<types::Float32Type>(t)) {
        return builder->getFloatTy();
    } else if (cast<types::Float64Type>(t)) {
        return builder->getDoubleTy();
    } else if (cast<types::BoolType>(t)) {
        return builder->getInt1Ty();
    } else if (cast<types::VoidType>(t)) {
        return builder->getVoidTy();
    }

    else if (auto f = cast<types::FunctionType>(t)) {
        return getLLVMFunctionType(f)->getPointerTo();
    } else {
        Syntax::E<BUG>(FMT("Undefined type! ('%s')", t->getName().c_str()));
    }

    return nullptr; // to avoid warnings
}

ptr<llvm::FunctionType>
LLVMBuilder::getLLVMFunctionType(ptr<types::FunctionType> fn) {
    auto argTypes =
        vector_iterate<std::shared_ptr<types::Type>, ptr<llvm::Type>>(
            fn->getArgs(),
            [&](std::shared_ptr<types::Type> arg) { return getLLVMType(arg); });

    auto ret = getLLVMType(fn->getRetType());
    return llvm::FunctionType::get(ret, argTypes, fn->isVariadic());
}

} // namespace codegen
} // namespace snowball