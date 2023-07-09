
#include "../../ir/values/Cast.h"
#include "../../utils/utils.h"
#include "LLVMBuilder.h"

#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>

#define IS_INTEGER(x)                                                                              \
    (utils::dyn_cast<types::Int8Type>(x) || utils::dyn_cast<types::Int16Type>(x) ||                \
     utils::dyn_cast<types::Int32Type>(x) || utils::dyn_cast<types::Int64Type>(x) ||               \
     utils::dyn_cast<types::BoolType>(x) || utils::dyn_cast<types::CharType>(x))
#define IS_FLOAT(x)                                                                                \
    (utils::dyn_cast<types::Float32Type>(x) || utils::dyn_cast<types::Float64Type>(x))

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
    if (IS_INTEGER(vTy) && IS_INTEGER(ty)) {
        this->value =
                builder->CreateIntCast(v, llvmType, true); // TODO: check if it's actually signed
    } else if (IS_INTEGER(vTy) && IS_FLOAT(ty)) {
        // cast signed integer to float
        this->value = builder->CreateSIToFP(v, llvmType);
    } else if (IS_FLOAT(vTy) && IS_INTEGER(ty)) {
        // cast float to signed integer
        this->value = builder->CreateFPToSI(v, llvmType);
    } else if (IS_FLOAT(ty) && IS_FLOAT(vTy)) {
        // cast float to another float
        this->value = builder->CreateFPCast(v, llvmType);
    } else if (utils::dyn_cast<types::ReferenceType>(ty)) {
        assert(utils::dyn_cast<types::ReferenceType>(vTy) ||
               utils::dyn_cast<types::CObjectType>(vTy));
        this->value = builder->CreatePointerCast(v, llvmType);
    } else if (utils::dyn_cast<types::NumericType>(vTy) &&
               utils::dyn_cast<types::CObjectType>(ty)) {
        this->value = builder->CreateIntToPtr(v, llvmType);
    } else {
        assert(utils::dyn_cast<types::DefinedType>(ty) || utils::dyn_cast<types::CObjectType>(ty));

        this->value = builder->CreatePointerCast(v, llvmType);
    }
}

} // namespace codegen
} // namespace snowball
