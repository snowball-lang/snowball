
#include "../../ir/values/Argument.h"
#include "../../utils/utils.h"
#include "LLVMBuilder.h"

#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>

namespace snowball {
namespace codegen {

void
LLVMBuilder::visit(ir::Argument* arg) {
    this->value = ctx->getSymbol(arg->getId());
}

} // namespace codegen
} // namespace snowball
