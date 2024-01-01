
#include "../../ir/values/EnumInit.h"
#include "../../utils/utils.h"
#include "LLVMBuilder.h"

#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>

namespace snowball {
namespace codegen {

void LLVMBuilder::visit(ir::EnumInit* ref) {
  Syntax::E<BUG>("EnumInit should not be visited!");
}

} // namespace codegen
} // namespace snowball
