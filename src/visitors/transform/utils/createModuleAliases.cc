
#include "../../Transformer.h"

using namespace snowball::utils;
using namespace snowball::Syntax;

namespace snowball {
namespace Syntax {

void Transformer::createModuleAliases(std::shared_ptr<ir::Module> mod, Statement::ImportStmt* import, const std::string& exportName) {
  auto aliases = import->getVariables();
  if (aliases.size() == 0) return;

  auto baseIdentifier = N<Expression::Identifier>(exportName);
  baseIdentifier->setDBGInfo(import->getDBGInfo());
  for (auto [alias, identifier] : aliases) {
    auto aliasIdentifier = N<Expression::Identifier>(alias);
    auto moduleIndex = N<Expression::Index>(baseIdentifier, aliasIdentifier, true);
    moduleIndex->setDBGInfo(import->getDBGInfo());
    auto item = std::make_shared<transform::Item>(moduleIndex);
    ctx->addItem(identifier, item);
  }
}

} // namespace Syntax
} // namespace snowball