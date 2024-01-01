
#include "../../ir/values/WhileLoop.h"
#include "../../utils/utils.h"
#include "LLVMBuilder.h"
#include "../../ir/values/EnumInit.h"

#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>

namespace snowball {
namespace codegen {

llvm::Value* LLVMBuilder::createEnumInit(ir::Call* call) {
    assert(false);
}

} // namespace codegen
} // namespace snowball
