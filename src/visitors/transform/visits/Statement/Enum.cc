#include "../../../Transformer.h"

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

SN_TRANSFORMER_VISIT(Statement::EnumTypeDef) {
  auto name = p_node->getName();
  auto uuid = ctx->createIdentifierName(name);
  auto state = ctx->saveState();
  auto x = ctx->cache->getType(uuid);
  if (x.has_value() && (!ctx->generateFunction)) {
    E<VARIABLE_ERROR>(
      p_node,
      FMT("enum with name '%s' is already defined in "
          "the current scope!",
          name.c_str())
    );
  } else if (!ctx->generateFunction || p_node->isGeneric()) {
    ctx->cache->setType(uuid, p_node, state);
    return;
  } else if (ctx->generateFunction && (!p_node->isGeneric())) {
    if (ctx->cache->getTransformedType(uuid) != std::nullopt) return;
    cacheComponents::Types::TypeStore store{.type = p_node, .state = state};
    (void)transformEnum(uuid, store);
    return;
  }
  assert(false);
}

} // namespace Syntax
} // namespace snowball