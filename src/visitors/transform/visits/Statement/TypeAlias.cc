#include "../../../Transformer.h"

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

SN_TRANSFORMER_VISIT(Statement::TypeAlias) {
  auto name = p_node->getIdentifier();
  auto uuid = ctx->createIdentifierName(name);
  auto state = ctx->saveState();
  auto x = ctx->cache->getType(uuid);
  if (x.has_value() && (!ctx->generateFunction)) {
    E<VARIABLE_ERROR>(
    p_node,
    FMT("Type alias with name '%s' is already "
        "defined in the current scope!",
        name.c_str())
    );
  } else if (ctx->generateFunction && (!p_node->isGeneric())) {
    if (ctx->cache->getTransformedType(uuid) != std::nullopt) return;
    auto baseType = transformType(p_node->getType());
    auto typeAlias = getBuilder().createTypeAlias(p_node->getDBGInfo(), name, baseType);
    typeAlias->setPrivacy(p_node->getPrivacy());
    typeAlias->unsafeSetUUID(uuid);
    auto item = std::make_shared<transform::Item>(typeAlias);
    ctx->cache->setTransformedType(uuid, item);
    ctx->addItem(name, item);
    return;
  } else if (!ctx->generateFunction || (p_node->getGenerics().size() > 0)) {
    ctx->cache->setType(uuid, p_node, state);
    return;
  }
  assert(false);
}

} // namespace Syntax
} // namespace snowball