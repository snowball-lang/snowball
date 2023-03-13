
#include "../../ir/values/Cast.h"
#include "../../utils/utils.h"
#include "LLVMBuilder.h"

#include <llvm-14/llvm/IR/Type.h>
#include <llvm-14/llvm/IR/Value.h>

namespace snowball {
namespace codegen {

void LLVMBuilder::visit(ptr<ir::Cast> c) {
    auto v = build(c->getExpr().get());
    auto vTy = c->getExpr()->getType();
    auto llvmValueType = getLLVMType(c->getExpr()->getType());
    auto ty = c->getCastType();
    auto llvmType = getLLVMType(ty);

    // Check if both types are integers
    if ((utils::dyn_cast<types::Int8Type>(vTy) ||
        utils::dyn_cast<types::Int16Type>(vTy) ||
        utils::dyn_cast<types::Int32Type>(vTy) ||
        utils::dyn_cast<types::Int64Type>(vTy)) &&
        (utils::dyn_cast<types::Int8Type>(ty) ||
        utils::dyn_cast<types::Int16Type>(ty) ||
        utils::dyn_cast<types::Int32Type>(ty) ||
        utils::dyn_cast<types::Int64Type>(ty))) {
        this->value = builder->CreateIntCast(v, llvmType, true); // TODO: check if it's actually signed
    } else if ((utils::dyn_cast<types::Int8Type>(vTy) ||
        utils::dyn_cast<types::Int16Type>(vTy) ||
        utils::dyn_cast<types::Int32Type>(vTy) ||
        utils::dyn_cast<types::Int64Type>(vTy)) &&
        (utils::dyn_cast<types::Float32Type>(ty) ||
        utils::dyn_cast<types::Float64Type>(ty))) {
        // cast signed integer to float
        this->value = builder->CreateSIToFP(v, llvmType);
    } else if ((utils::dyn_cast<types::Float32Type>(ty) ||
        utils::dyn_cast<types::Float64Type>(ty)) &&
        (utils::dyn_cast<types::Int8Type>(vTy) ||
        utils::dyn_cast<types::Int16Type>(vTy) ||
        utils::dyn_cast<types::Int32Type>(vTy) ||
        utils::dyn_cast<types::Int64Type>(vTy))) {
        // cast float to signed integer
        this->value = builder->CreateFPToSI(v, llvmType);
    } else if ((utils::dyn_cast<types::Float32Type>(ty) ||
        utils::dyn_cast<types::Float64Type>(ty)) &&
        (utils::dyn_cast<types::Float32Type>(ty) ||
        utils::dyn_cast<types::Float64Type>(ty))) {
        // cast float to another float
        this->value = builder->CreateFPCast(v, llvmType);
    } else {
        assert(utils::dyn_cast<types::DefinedType>(ty) != nullptr);
        assert(utils::dyn_cast<types::DefinedType>(vTy) != nullptr);

        this->value = builder->CreatePointerCast(v, llvmType);
    }
}

} // namespace codegen
} // namespace snowball
