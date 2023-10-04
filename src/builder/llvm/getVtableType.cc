
#include "../../utils/utils.h"
#include "LLVMBuilder.h"

#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>

namespace snowball {
namespace codegen {

llvm::StructType* LLVMBuilder::getVtableType(types::DefinedType* ty) {
  auto t = llvm::StructType::create(*context, (std::string)_SN_VTABLE_PREFIX + ty->getMangledName());
  auto arrType = llvm::ArrayType::get(llvm::Type::getInt8PtrTy(*context), ty->getVtableSize() + 2);
  t->setBody(arrType);
  ctx->addVtableTy(ty->getId(), t);
  return t;
}

} // namespace codegen
} // namespace snowball