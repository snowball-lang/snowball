
#include "../../ir/values/Call.h"
#include "../../services/OperatorService.h"
#include "../../utils/utils.h"
#include "LLVMBuilder.h"

#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/GlobalVariable.h>
#include <llvm/IR/Metadata.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>

namespace snowball {
namespace codegen {

llvm::GlobalVariable* LLVMBuilder::createVirtualTable(types::BaseType* ty, llvm::StructType* vtableType) {
  auto structName = (std::string) _SN_VTABLE_PREFIX + ty->getMangledName();

  std::vector<llvm::Constant*> functions = {
          llvm::ConstantPointerNull::get(llvm::Type::getInt8PtrTy(*context)),
          llvm::ConstantPointerNull::get(llvm::Type::getInt8PtrTy(*context)), // TODO: class info
  };
  ty = ctx->typeInfo.at(ty->getId()).get();
  for (auto fn : ty->getVTable()) {
    if (fn->isDeclaration()) {
      functions.push_back(llvm::ConstantPointerNull::get(llvm::Type::getInt8PtrTy(*context)));
      continue;
    }

    auto c = llvm::cast<llvm::Constant>(funcs.at(fn->getId()));
    functions.push_back(c);
  }

  auto vTy = ctx->getVtableTy(ty->getId());
  assert(vTy && "Vtable type not found!");
  vTy->setBody(llvm::ArrayType::get(llvm::Type::getInt8PtrTy(*context), functions.size()));

  module->getOrInsertGlobal(structName, vtableType);
  auto vTable = module->getNamedGlobal(structName);
  vTable->setLinkage(llvm::GlobalValue::LinkageTypes::InternalLinkage);
  vTable->setConstant(true);
  vTable->setDSOLocal(true);
  vTable->setUnnamedAddr(llvm::GlobalValue::UnnamedAddr::Global);

  // set comdat any
#ifdef __linux__
  vTable->setComdat(module->getOrInsertComdat(structName));
#endif

  auto arr = llvm::ConstantArray::get(
          llvm::ArrayType::get(llvm::Type::getInt8PtrTy(*context), functions.size()), functions
  );
  auto s = llvm::ConstantStruct::get(vtableType, arr);
  vTable->setInitializer(s);
  return vTable;
}

} // namespace codegen
} // namespace snowball
