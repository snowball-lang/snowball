
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
    if (ctx->getCurrentFunction()->getName() =="_ZN$SNpkg::home::mauro::work::snowball::tests::lambdas.sn.test&40return_lambda_with_parent_scope::.$LmbdFCv14112SaFnE" && v->getIdentifier() == "a") {
      DUMP_S("heyh")
    }
    GET_VAR_IMPL(v, value);
  } else {
    assert(false && "BUG: Value extract type not supported!");
  }

  this->value = value;
}

} // namespace codegen
} // namespace snowball
