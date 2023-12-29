
#include "../../ir/values/ReferenceTo.h"
#include "../../utils/utils.h"
#include "LLVMBuilder.h"

#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>

namespace snowball {
namespace codegen {

void LLVMBuilder::visit(ir::ReferenceTo* ref) {
  auto val = ref->getValue();
  auto llvmReferencedValue = build(val.get());

  auto tempVal = (llvm::Value*) nullptr;
  if (llvm::isa<llvm::Constant>(llvmReferencedValue) && !llvm::isa<llvm::GlobalVariable>(llvmReferencedValue)) {
    auto var = new llvm::GlobalVariable(
      *module,
      getLLVMType(val->getType()),
      false,
      llvm::GlobalValue::LinkageTypes::InternalLinkage,
      llvm::cast<llvm::Constant>(llvmReferencedValue),
      "alloca_" + utils::gen_random<32>()
    );
    var->setUnnamedAddr(llvm::GlobalValue::UnnamedAddr::Global);
    tempVal = var;
  } else {
    if (llvm::isa<llvm::LoadInst>(llvmReferencedValue)) {
      llvmReferencedValue = llvm::cast<llvm::LoadInst>(llvmReferencedValue)->getPointerOperand();
    }
    tempVal = llvmReferencedValue;
  }

  ctx->doNotLoadInMemory = true;
  this->value = tempVal;
}

} // namespace codegen
} // namespace snowball
