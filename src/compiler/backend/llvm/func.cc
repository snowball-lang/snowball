
#include "compiler/backend/llvm/builder.h"

namespace snowball {
namespace backend {

void LLVMBuilder::emit(sil::FuncDecl* node) {
  if (just_declare) {
    assert(node->get_type()->is_func());
    auto fn_type = get_func_type(node->get_type()->as_func());
    auto fn = llvm::Function::Create(fn_type, llvm::Function::ExternalLinkage, node->get_name(), *module);
  }
}

}
} // namespace snowball
