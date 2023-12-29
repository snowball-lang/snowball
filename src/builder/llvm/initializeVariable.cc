#include "../../utils/utils.h"
#include "LLVMBuilder.h"

#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>

namespace snowball {
namespace codegen {

void LLVMBuilder::initializeVariable(llvm::Value* var, llvm::Type* ty, unsigned int size) {
  assert(llvm::isa<llvm::StructType>(ty));
  auto llvmType = llvm::cast<llvm::StructType>(ty);
  auto initializerName =
          FMT("__const.default.%s", llvmType->getName().str().c_str());
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
    auto structInitializer = llvm::ConstantStruct::get(llvmType, elements);
    constInitializer = new llvm::GlobalVariable(
            *module,
            llvmType,
            true,
            llvm::GlobalValue::PrivateLinkage,
            structInitializer,
            initializerName,
            nullptr,
            llvm::GlobalVariable::NotThreadLocal
    );
    constInitializer->setUnnamedAddr(llvm::GlobalValue::UnnamedAddr::Global);
  }

  auto dataLayout = module->getDataLayout();
  auto layout = dataLayout.getTypeStoreSize(llvmType);
  builder->CreateMemCpy(var, llvm::MaybeAlign(), constInitializer, llvm::MaybeAlign(), layout);
}

} // namespace codegen
} // namespace snowball
