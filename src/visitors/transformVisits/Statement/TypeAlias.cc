#include "../../Transformer.h"

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

SN_TRANSFORMER_VISIT(Statement::TypeAlias) {
    auto name = p_node->getIdentifier();
    auto uuid = ctx->createIdentifierName(name);

    auto state = ctx->saveState();
    auto x     = ctx->cache->getType(uuid);

    if (x.has_value() && (!ctx->generateFunction)) {
        E<VARIABLE_ERROR>(
            p_node,
            FMT("Type alias with name '%s' is already defined in the current scope!",
                name.c_str()));
    } else if ((!x.has_value()) && (p_node->getGenerics().size() == 0)) {
        if (!ctx->generateFunction) return;
        assert(ctx->cache->getTransformedType(uuid) == std::nullopt);

        auto item = std::make_shared<transform::Item>(transformType(p_node->getType()));
        ctx->cache->setTransformedType(uuid, item);

        return;
    } else if ((p_node->getGenerics().size() > 0)) {
        ctx->cache->setType(uuid, p_node, state);
        return;
    }

    assert(false);
}

} // namespace Syntax
} // namespace snowball