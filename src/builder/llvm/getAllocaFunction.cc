
#include "../../utils/utils.h"
#include "LLVMBuilder.h"

#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>

namespace snowball {
namespace codegen {

llvm::Function* LLVMBuilder::getAllocaFunction() {
  auto ty = llvm::FunctionType::get(builder->getInt8PtrTy(), {builder->getInt32Ty()}, false);
  auto f = llvm::cast<llvm::Function>(module->getOrInsertFunction(getSharedLibraryName("sn.alloca"), ty).getCallee());
  f->addRetAttr(llvm::Attribute::NonNull);
  f->addRetAttr(llvm::Attribute::NoAlias);
  f->addRetAttr(llvm::Attribute::NoUndef);
  f->setDoesNotThrow();
  f->setCannotDuplicate();
  f->setDoesNotRecurse();
  return f;
}

} // namespace codegen
} // namespace snowball
