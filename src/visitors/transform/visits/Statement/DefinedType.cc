#include "../../../Transformer.h"

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

SN_TRANSFORMER_VISIT(Statement::DefinedTypeDef) {
  auto name = p_node->getName();
  auto uuid = ctx->createIdentifierName(name);

  auto state = ctx->saveState();
  auto x = ctx->cache->getType(uuid);

  if (p_node->hasAttribute(Attributes::CLASS_EXTENDS)) {
    transformTypeExtension(p_node, uuid);
    return;
  }

  if (x.has_value() && (!ctx->generateFunction)) {
    E<VARIABLE_ERROR>(p_node,
            FMT("Class with name '%s' is already defined in "
                "the current scope!",
                    name.c_str()));
  } else if (!ctx->generateFunction || (p_node->getGenerics().size() > 0)) {
    ctx->cache->setType(uuid, p_node, state);
    return;
  } else if (ctx->generateFunction && (p_node->getGenerics().size() == 0)) {
    if (ctx->cache->getTransformedType(uuid) != std::nullopt) return;
    cacheComponents::Types::TypeStore store{.type = p_node, .state = state};
    transformClass(uuid, store);
    return;
  }

  assert(false);
}

} // namespace Syntax
} // namespace snowball