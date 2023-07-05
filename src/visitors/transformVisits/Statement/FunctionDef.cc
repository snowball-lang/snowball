#include "../../../services/OperatorService.h"
#include "../../Transformer.h"

#include <cstring>

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

#define IS_MAIN                                                                                    \
    (name == "main" && p_node->getPrivacy() == Statement::Privacy::PUBLIC && ctx->module->isMain())

#define ADD_SELF_ARG                                                                               \
    if (auto c = ctx->getCurrentClass(true)) {                                                     \
        auto args = p_node->getArgs();                                                             \
        auto pointer = c->getPointerTo();                                                          \
        pointer->setMutable(p_node->isMutable() || p_node->isConstructor());                       \
        if (!(args.size() > 0 && args.at(0)->getName() == "self") && !p_node->isStatic()) {        \
            auto self = new Expression::Param("self", pointer->toRef());                           \
                                                                                                   \
            args.insert(args.begin(), self);                                                       \
            p_node->setArgs(args);                                                                 \
        } else if (!p_node->isStatic()) { /* "self" already set by another class */                \
            args.at(0)->setType(pointer->toRef());                                                 \
        }                                                                                          \
    }

namespace snowball {
namespace Syntax {

SN_TRANSFORMER_VISIT(Statement::FunctionDef) {
    auto name = p_node->getName();
    ADD_SELF_ARG

    if (!ctx->generateFunction && !IS_MAIN) {
        // assert(!services::OperatorService::isOperator(name));
        //  Check if the function requirements match the main function
        auto uuid = ctx->createIdentifierName(name);

        // Just set it to the function stack
        if (auto x = ctx->cache->getFunction(uuid)) {
            // assert(false && "func exists");
            // TODO: check for already existing functions
        }

        ctx->cache->setFunction(uuid, p_node, ctx->saveState());
        return;
    }

    if (ctx->generateFunction && IS_MAIN) {
        transformMainFunction(p_node);
        return;
    }

    if (ctx->generateFunction && p_node->getGenerics().size() == 0) {
        transformFunction({p_node, ctx->saveState()}, {});
    }
}

} // namespace Syntax
} // namespace snowball
