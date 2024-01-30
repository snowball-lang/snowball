
#include "../../ir/values/Argument.h"
#include "../../utils/utils.h"
#include "LLVMBuilder.h"

#include "varFetchImpl.h"

#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>

namespace snowball {
namespace codegen {

void LLVMBuilder::visit(ir::Argument* variable) {
  GET_VAR_IMPL(variable, value)
}

} // namespace codegen
} // namespace snowball
