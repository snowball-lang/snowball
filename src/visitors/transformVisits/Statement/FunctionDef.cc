#include "../../../services/OperatorService.h"
#include "../../Transformer.h"

#include <cstring>

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

#define IS_MAIN                                                                \
    (name == "main" && p_node->getPrivacy() == Statement::Privacy::PUBLIC &&   \
     ctx->module->isMain())

namespace snowball {
namespace Syntax {

SN_TRANSFORMER_VISIT(Statement::FunctionDef) {
    auto name = p_node->getName();
    if (!ctx->generateFunction && !(IS_MAIN)) {
        assert(!services::OperatorService::isOperator(name));
        // Check if the function requirements match the main function

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
        return;
    }

    if (ctx->generateFunction && IS_MAIN) {
        transformMainFunction(p_node);
        return;
    }

        DUMP_S(name.c_str());

    if (ctx->generateFunction && p_node->getGenerics().size() == 0) {

        if (services::OperatorService::opEquals<services::OperatorService::CONSTRUCTOR>(name)) {
            auto c = ctx->getCurrentClass();
            assert(c != nullptr);

            p_node->setRetType(c->toRef());
        }

        transformFunction({p_node, ctx->saveState()}, {});
    }
}

} // namespace Syntax
} // namespace snowball
