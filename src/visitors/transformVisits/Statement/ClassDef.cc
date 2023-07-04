#include "../../Transformer.h"

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

SN_TRANSFORMER_VISIT(Statement::DefinedTypeDef) {
    auto name = p_node->getName();
    auto uuid = ctx->createIdentifierName(name);

    auto state = ctx->saveState();
    auto x = ctx->cache->getType(uuid);

    if (x.has_value() && (!ctx->generateFunction) ||
        (ctx->cache->getTransformedType(uuid) != std::nullopt)) {
        E<VARIABLE_ERROR>(p_node,
                          FMT("Class with name '%s' is already defined in "
                              "the current scope!",
                              name.c_str()));
    } else if ((!x.has_value()) && (p_node->getGenerics().size() == 0)) {
        if (!ctx->generateFunction) return;
        assert(ctx->cache->getTransformedType(uuid) == std::nullopt);
        cacheComponents::Types::TypeStore store{.type = p_node, .state = state};
        transformClass(uuid, store);
        return;
    } else if ((p_node->getGenerics().size() > 0)) {
        ctx->cache->setType(uuid, p_node, state);
        return;
    }

    assert(false);
}

} // namespace Syntax
} // namespace snowball