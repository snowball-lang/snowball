
#include "compiler/globals.h"
#include "compiler/backend/llvm/builder.h"

namespace snowball {
namespace backend {

void CommentWriter::printInfoComment(const llvm::Value& I,
                                  llvm::formatted_raw_ostream& OS) {
  OS << "; [#uses=" << I.getNumUses();
  if (llvm::isa<llvm::GetElementPtrInst>(&I) || llvm::isa<llvm::LoadInst>(&I) ||
      llvm::isa<llvm::StoreInst>(&I)) {
    OS << ", #type=" << *I.getType();
  } else if (llvm::isa<llvm::AllocaInst>(&I)) {
    auto alloca = llvm::cast<llvm::AllocaInst>(&I);
    OS << ", size/bytes=" << DL.getTypeAllocSize(alloca->getAllocatedType());
  }
  const auto* instr = llvm::dyn_cast<llvm::Instruction>(&I);
  if (instr) {
    if (auto sub = instr->getDebugLoc()) {
      OS << ", #line=" << sub->getLine();
    }
  }
  OS << "]";
}

void CommentWriter::emitFunctionAnnot(const llvm::Function* F, llvm::formatted_raw_ostream& OS) {
  OS << "; [#uses=" << F->getNumUses() << "]\n"; // Output # uses
  if (auto sub = F->getSubprogram())
    OS << "; [#name=" << sub->getName() << "]\n"; // Output # uses
}

}
}
