#include "../../../../services/OperatorService.h"
#include "../../../Transformer.h"

#include <cstring>

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

#define IS_PUBLIC (p_node->getPrivacy() == Statement::Privacy::PUBLIC)
#define IS_MAIN   (name == "main" && ctx->module->isMain())

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

    if (!ctx->generateFunction && !(IS_MAIN)) {
        // assert(!services::OperatorService::isOperator(name));
        //  Check if the function requirements match the main function
        auto uuid = ctx->createIdentifierName(name);
        // TODO: check for already existing functions (for no mangled versions)
        if (p_node->hasAttribute(Attributes::Fn::NO_MANGLE)) {
            if (std::find(ctx->exported.begin(), ctx->exported.end(), name) !=
                ctx->exported.end()) {
                E<VARIABLE_ERROR>(p_node->getDBGInfo(), "Unmangled export already exists!",
                                  {.info = "This function name is already exported as unmangled.",
                                   .note = "This symbols is exported on another location with the "
                                           "'no_mangle' attribute.",
                                   .help = "Try renaming the function or removing the 'no_mangle' "
                                           "attribute. If you want \n"
                                           "to export the function as unmangled, remove the "
                                           "mangled version of the function."});
            } else {
                ctx->exported.push_back(name);
            }
        }
        ctx->cache->setFunction(uuid, p_node, ctx->saveState());
        return;
    }

    if (ctx->generateFunction && IS_MAIN) {
        if (!IS_PUBLIC) E<SYNTAX_ERROR>(p_node, "Program entry point must be public!");
        transformMainFunction(p_node);
        return;
    }

    if (ctx->generateFunction && p_node->getGenerics().size() == 0) {
        transformFunction({p_node, ctx->saveState()}, {});
    }
}

} // namespace Syntax
} // namespace snowball
