
#include "../../ir/values/Cast.h"
#include "../../utils/utils.h"
#include "LLVMBuilder.h"

#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>

#define IS_INTEGER(x) (utils::is<types::IntType>(x) || utils::is<types::CharType>(x))
#define IS_FLOAT(x)   (utils::is<types::FloatType>(x))
#define IS_DEFINED(x) (utils::is<types::DefinedType>(x) || utils::is<types::InterfaceType>(x))

namespace snowball {
namespace codegen {

void LLVMBuilder::visit(ir::Cast* c) {
  auto v = build(c->getExpr().get());
  auto vTy = c->getExpr()->getType();
  auto llvmValueType = getLLVMType(vTy);
  auto ty = c->getCastType();
  auto llvmType = getLLVMType(ty);

  v = load(v, vTy);

  if (v->getType() == llvmType) {
    // note: this will always be true for pointer casting since llvm 15 (using opaque pointers)
    this->ctx->doNotLoadInMemory = true;
    this->value = v;
    return;
  }

  // Check if both types are integers
  if (IS_INTEGER(vTy) && IS_INTEGER(ty)) {                    // i[n] <-> i[n]
    this->value = builder->CreateIntCast(v, llvmType, false); // TODO: check if it's actually signed
  } else if (IS_INTEGER(vTy) && IS_FLOAT(ty)) {               // i[n] -> float
    // cast signed integer to float
    this->value = builder->CreateSIToFP(v, llvmType);
  } else if (IS_FLOAT(vTy) && IS_INTEGER(ty)) { // float -> i[n]
    // cast float to signed integer
    this->value = builder->CreateFPToSI(v, llvmType);
  } else if (IS_FLOAT(ty) && IS_FLOAT(vTy)) { // float <-> float
    // cast float to another float
    this->value = builder->CreateFPCast(v, llvmType);
  } else if (IS_INTEGER(vTy) && utils::cast<types::PointerType>(ty)) { // i[n] -> *
    this->value = builder->CreateIntToPtr(v, llvmType);
    this->ctx->doNotLoadInMemory = true;
  } else if (IS_DEFINED(vTy) && IS_DEFINED(ty)) {
    v->dump();
    if (llvm::isa<llvm::LoadInst>(v)) {
      auto ptr = llvm::cast<llvm::LoadInst>(v)->getPointerOperand();
      this->value = builder->CreateLoad(llvmType, ptr);
    } else if (llvm::isa<llvm::AllocaInst>(v)) {
      this->value = builder->CreateLoad(llvmType, v);
      ctx->doNotLoadInMemory = true;
    } else {
      assert(!"Unreachable type case found!");
    }
  } else {
    assert(utils::cast<types::ReferenceType>(ty) || utils::cast<types::PointerType>(ty));
    this->value = builder->CreatePointerCast(v, llvmType);
    this->ctx->doNotLoadInMemory = true;
  }
}

} // namespace codegen
} // namespace snowball
