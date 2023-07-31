
#include "../../ir/values/Dereference.h"
#include "../../utils/utils.h"
#include "LLVMBuilder.h"

#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>

namespace snowball {
namespace codegen {

void LLVMBuilder::visit(ir::DereferenceTo* ref) {
  auto val = ref->getValue();
  auto type = ref->getType();

  auto llvmVal = build(val.get());
  if (utils::cast<types::DefinedType>(type) && llvm::isa<llvm::LoadInst>(llvmVal)) { // not a pointer
    llvmVal = llvm::cast<llvm::LoadInst>(llvmVal)->getOperand(0);
    //if (llvm::isa<llvm::AllocaInst>(llvmVal)) {
    //  auto entryBlock = ctx->getCurrentFunction()->getEntryBlock().getTerminator();
    //  auto backupBlock = builder->GetInsertBlock();
    //  builder->SetInsertPoint(entryBlock);
    //  auto alloca = builder->CreateAlloca(getLLVMType(type));
    //  builder->SetInsertPoint(backupBlock);
    //  auto load = builder->CreateLoad(getLLVMType(type), llvmVal);
    //  builder->CreateMemCpy(alloca, llvm::MaybeAlign(), load, llvm::MaybeAlign(),
    //          module->getDataLayout().getTypeAllocSize(getLLVMType(type)), 0);
    //  llvmVal = alloca;
    //}
     
    this->value = builder->CreateLoad(getLLVMType(type), llvmVal);
    return;
  }

  this->value = builder->CreateLoad(getLLVMType(type), llvmVal);
}

} // namespace codegen
} // namespace snowball
