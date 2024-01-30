
#include "../../ir/values/ValueExtract.h"
#include "../../utils/utils.h"
#include "LLVMBuilder.h"

#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>
#include <memory>
#include "varFetchImpl.h"

namespace snowball {
namespace codegen {

void LLVMBuilder::visit(ir::ValueExtract* extract) {
  auto var = extract->getValue();
  llvm::Value* value = nullptr;
  if (auto f = utils::dyn_cast<ir::Func>(var)) {
    ctx->doNotLoadInMemory = true;
    auto fn = funcs.at(f->getId());
    this->value = fn;
    return;
  } else if (auto v = utils::dyn_cast<ir::Variable>(var)) {
    GET_VAR_IMPL(v, value);
  } else {
    assert(false && "BUG: Value extract type not supported!");
  }
  this->value = value;
}

} // namespace codegen
} // namespace snowball
