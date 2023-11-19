#include "../../../../ir/values/TryCatch.h"
#include "../../../Transformer.h"

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

SN_TRANSFORMER_VISIT(Statement::TryCatch) {
  auto tryBlock = utils::dyn_cast<ir::Block>(trans(p_node->getTryBlock()));
  std::vector<std::shared_ptr<ir::Block>> catchBlocks;
  std::vector<std::shared_ptr<ir::VariableDeclaration>> catchVars;

  for (auto catchBlock : p_node->getCatchBlocks()) {
    auto name = catchBlock->getExceptionVar();
    auto type = transformSizedType(catchBlock->getExceptionType(), false, "Cannot catch unsized type '%s'");
    auto block = catchBlock->getBlock();

    ctx->withScope([&] {
      auto var = getBuilder().createVariable(block->getDBGInfo(), name, type, ctx->getScopeIndex());
      auto varDecl = getBuilder().createVariableDeclaration(p_node->getDBGInfo(), var, nullptr);
      varDecl->setId(var->getId());
      getBuilder().setType(varDecl, type);

      auto item = std::make_shared<transform::Item>(transform::Item::VALUE, var);
      ctx->addItem(name, item);

      catchBlocks.push_back(utils::dyn_cast<ir::Block>(trans(block)));
      catchVars.push_back(varDecl);
      ctx->getCurrentFunction()->addSymbol(varDecl);
    });
  }

  auto tryCatch = getBuilder().createTryCatch(p_node->getDBGInfo(), tryBlock, catchBlocks, catchVars);
  this->value = tryCatch;
}

} // namespace Syntax
} // namespace snowball