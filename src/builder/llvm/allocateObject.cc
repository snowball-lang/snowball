#include "../../utils/utils.h"
#include "LLVMBuilder.h"

#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>

namespace snowball {
namespace codegen {

llvm::Value* LLVMBuilder::allocateObject(types::DefinedType* ty) {
  auto llvmType = llvm::cast<llvm::StructType>(getLLVMType(ty));
  llvm::Value* cast = createAlloca(llvmType, FMT(".alloc.%s", llvmType->getStructName()));

  initializeVariable(cast, llvmType, ty->sizeOf());
  return cast;
}

} // namespace codegen
} // namespace snowball
