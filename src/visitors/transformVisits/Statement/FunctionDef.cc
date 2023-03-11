#include "../../Transformer.h"

#include <cstring>

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

SN_TRANSFORMER_VISIT(Statement::FunctionDef) {

    auto name = p_node->getName();

    // Check if the function requirements match the main function
    if (name == "main" && p_node->getPrivacy() == Statement::Privacy::PUBLIC &&
        ctx->module->isMain()) {
        transformMainFunction(p_node);
        return;
    }

    auto uuid = ctx->createIdentifierName(name);
    if (auto c = ctx->getCurrentClass()) {
        if (!p_node->isStatic()) {
            auto args = p_node->getArgs();
            auto self = new Expression::Param("self", c->toRef());

            args.insert(args.begin(), self);
            p_node->setArgs(args);
        }
    }

    // Just set it to the function stack
    if (auto x = ctx->cache->getFunction(uuid)) {
        // assert(false && "func exists");
        // TODO: check for already existing functions
    }

    ctx->cache->setFunction(uuid, p_node, ctx->saveState());
}

} // namespace Syntax
} // namespace snowball
