
#include "../../ir/values/Cast.h"
#include "../../utils/utils.h"
#include "LLVMBuilder.h"

#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>

#define IS_INTEGER(x)                                                                                                  \
    (utils::cast<types::Int8Type>(x) || utils::cast<types::Int16Type>(x) ||                                    \
     utils::cast<types::Int32Type>(x) || utils::cast<types::Int64Type>(x) ||                                   \
     utils::cast<types::BoolType>(x) || utils::cast<types::CharType>(x))
#define IS_FLOAT(x) (utils::cast<types::Float32Type>(x) || utils::cast<types::Float64Type>(x))

namespace snowball {
namespace codegen {

void LLVMBuilder::visit(ir::Cast* c) {
    auto v = build(c->getExpr().get());
    auto vTy = c->getExpr()->getType();
    auto llvmValueType = getLLVMType(vTy);
    auto ty = c->getCastType();
    auto llvmType = getLLVMType(ty);

    // TODO: cobj casting

    // Check if both types are integers
    if (IS_INTEGER(vTy) && IS_INTEGER(ty)) {                     // i[n] <-> i[n]
        this->value = builder->CreateIntCast(v, llvmType, false); // TODO: check if it's actually signed
    } else if (IS_INTEGER(vTy) && IS_FLOAT(ty)) {                // i[n] -> float
        // cast signed integer to float
        this->value = builder->CreateSIToFP(v, llvmType);
    } else if (IS_FLOAT(vTy) && IS_INTEGER(ty)) { // float -> i[n]
        // cast float to signed integer
        this->value = builder->CreateFPToSI(v, llvmType);
    } else if (IS_FLOAT(ty) && IS_FLOAT(vTy)) { // float <-> float
        // cast float to another float
        this->value = builder->CreateFPCast(v, llvmType);
    } else if (utils::cast<types::ReferenceType>(ty)) { // ref <-> cobj
        assert(utils::cast<types::ReferenceType>(vTy) || utils::cast<types::CObjectType>(vTy));
        this->value = builder->CreatePointerCast(v, llvmType);
    } else if (utils::cast<types::NumericType>(vTy) && // i[n] -> cobj
               utils::cast<types::CObjectType>(ty)) {
        this->value = builder->CreateIntToPtr(v, llvmType);
    } else if (utils::cast<types::NumericType>(ty) && utils::cast<types::CObjectType>(vTy)) { // cobj -> i[n]
        this->value = builder->CreatePtrToInt(v, llvmType);
    } else {
        assert(utils::cast<types::BaseType>(ty) || utils::cast<types::CObjectType>(ty));
        this->value = builder->CreatePointerCast(v, llvmType);
    }
}

} // namespace codegen
} // namespace snowball
