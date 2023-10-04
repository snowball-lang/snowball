#include "../../utils/utils.h"
#include "LLVMBuilder.h"

#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>

namespace snowball {
namespace codegen {

llvm::Value* LLVMBuilder::allocateObject(types::DefinedType* ty) {
  auto llvmType = llvm::cast<llvm::StructType>(getLLVMType(ty));
  llvm::Value* cast = builder->CreateAlloca(llvmType, nullptr, FMT(".alloc.%s", llvmType->getStructName()));

  auto initializerName = FMT("__const.%s.%s", ctx->getCurrentFunction()->getName().str().c_str(), ty->getName().c_str());
  auto constInitializer = module->getNamedGlobal(initializerName);
  if (!constInitializer) {
    std::vector<llvm::Constant*> elements;
    for (auto field : llvmType->elements()) {
      if (field->isPointerTy()) {
        elements.push_back(llvm::ConstantPointerNull::get(llvm::cast<llvm::PointerType>(field)));
      } else if (field->isStructTy()) {
        elements.push_back(llvm::UndefValue::get(field));
      } else {
        elements.push_back(llvm::Constant::getNullValue(field));
      }
    }
    auto structInitializer = llvm::ConstantStruct::get((llvm::StructType*)llvmType, elements);
    constInitializer = new llvm::GlobalVariable(
            *module, llvmType, true, llvm::GlobalValue::PrivateLinkage, structInitializer, initializerName,
            nullptr, llvm::GlobalVariable::NotThreadLocal);
    constInitializer->setUnnamedAddr(llvm::GlobalValue::UnnamedAddr::Global);
  }

  //builder->CreateMemCpy(cast, llvm::MaybeAlign(), constInitializer, llvm::MaybeAlign(), ty->sizeOf());
  return cast;
}

} // namespace codegen
} // namespace snowball
