
#include "compiler/backend/llvm/builder.h"

namespace snowball {
namespace backend {

void LLVMBuilder::emit(const sil::VarDecl* node) {
  auto alloca = alloc(node->get_type(), "__var." + node->get_name());
  auto loc = node->get_location();
  auto file = dbg.get_file(loc.file->get_path());
  auto dbg_var = dbg.builder->createAutoVariable(
    dbg.scope, node->get_name(), file, loc.line,
    get_ditype(node->get_type()), dbg.debug);
  dbg.builder->insertDeclare(
    alloca, dbg_var, dbg.builder->createExpression(),
    llvm::DILocation::get(*llvm_ctx, loc.line, loc.column, dbg.scope),
    builder->GetInsertBlock());
  if (node->get_value()) {
    auto value = expr(node->get_value().value());
    builder->CreateStore(value, alloca);
  }
  builder_ctx.set_value(node->get_id(), alloca);
  value = alloca;
}

}
} // namespace snowball
