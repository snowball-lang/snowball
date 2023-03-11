#include "../../Transformer.h"

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

SN_TRANSFORMER_VISIT(Statement::ClassDef) {
    auto name = p_node->getName();
    auto uuid = ctx->createIdentifierName(name);

    if (auto x = ctx->cache->getType(uuid)) {
        E<VARIABLE_ERROR>(
            p_node,
            FMT("Class with name '%s' is already defined in the current scope!",
                name.c_str()));
    }

    ctx->cache->setType(uuid, p_node, ctx->saveState());
}

} // namespace Syntax
} // namespace snowball