
#include "compiler/utils/utils.h"
#include "compiler/backend/llvm/builder.h"

namespace snowball {
namespace backend {

void LLVMBuilder::emit(const sil::Reference* node) {
  auto val = node->get_value();
  auto llvm_val = build(val);
  auto temp_val = (llvm::Value*)nullptr;
  if (llvm::isa<llvm::Constant>(llvm_val) 
    && !llvm::isa<llvm::GlobalVariable>(llvm_val)) {
    auto var = new llvm::GlobalVariable(
      *builder_ctx.module,
      get_type(val->get_type()),
      false,
      llvm::GlobalValue::LinkageTypes::InternalLinkage,
      llvm::cast<llvm::Constant>(llvm_val),
      "alloca_" + utils::gen_random_string<32>()
    );
    var->setUnnamedAddr(llvm::GlobalValue::UnnamedAddr::Global);
    temp_val = var;
  } else {
    if (llvm::isa<llvm::LoadInst>(llvm_val)) {
      llvm_val = llvm::cast<llvm::LoadInst>(llvm_val)->getPointerOperand();
    }
    temp_val = llvm_val;
  }
  builder_ctx.dont_load = true;
  value = temp_val;
}

}
} // namespace snowball
