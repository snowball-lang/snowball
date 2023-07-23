
#include "../../utils/utils.h"
#include "LLVMBuilder.h"

#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>

namespace snowball {
namespace codegen {

llvm::StructType* LLVMBuilder::getTypeInfoType() {
    return llvm::StructType::get(builder->getInt32Ty());
}

} // namespace codegen
} // namespace snowball
