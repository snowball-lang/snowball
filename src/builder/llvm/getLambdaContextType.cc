
#include "../../utils/utils.h"
#include "LLVMBuilder.h"

#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>

namespace snowball {
namespace codegen {

llvm::StructType* LLVMBuilder::getLambdaContextType() {
  return llvm::StructType::get(builder->getInt8PtrTy(), builder->getInt8PtrTy());
}

} // namespace codegen
} // namespace snowball
