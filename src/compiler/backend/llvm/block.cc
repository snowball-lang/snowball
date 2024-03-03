
#include "compiler/backend/llvm/builder.h"

namespace snowball {
namespace backend {

void LLVMBuilder::emit(const sil::Block* node) {
  auto block = llvm::BasicBlock::Create(*llvm_ctx, "bb", builder_ctx.get_current_func());
  builder->CreateBr(block);
  builder->SetInsertPoint(block);
  auto backup_scope = dbg.scope;
  auto loc = node->get_location();
  dbg.scope = llvm::DILexicalBlock::get(*llvm_ctx, backup_scope, dbg.get_file(loc.file->get_path()), loc.line, loc.column);
  for (const auto& stmt : node->get_insts())
    build(stmt);
  dbg.scope = backup_scope;
}

}
} // namespace snowball

