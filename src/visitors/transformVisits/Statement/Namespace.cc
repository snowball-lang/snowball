#include "../../../ir/values/Cast.h"
#include "../../Transformer.h"

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

SN_TRANSFORMER_VISIT(Statement::Namespace) {
    if (!ctx->generateFunction) return;
    auto name = p_node->getName();
    auto body = p_node->getBody();
    if (ctx->getInScope(name, ctx->currentScope()).second)
        E<VARIABLE_ERROR>(p_node, FMT("Namespace '%s' is already defined in the current scope!", name.c_str()));
    auto mod = std::make_shared<ir::Module>(getNameWithBase(name), ctx->createIdentifierName(name));
    mod->setSourceInfo(ctx->module->getSourceInfo());
    ctx->uuidStack.push_back(ctx->module->getUniqueName());
    auto backup = ctx->module;
    ctx->module = mod;
    ctx->withScope(
        [&]() mutable {
            for (auto x : body) { x->accept(this); }
        });
    ctx->module = backup;
    addModule(mod);
    auto sharedModule = std::make_shared<Item>(mod);
    ctx->addItem(name, sharedModule);
    ctx->uuidStack.pop_back();
}

} // namespace Syntax
} // namespace snowball