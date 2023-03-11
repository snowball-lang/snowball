
#include "../Transformer.h"

#include <optional>

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

Transformer::StoreType Transformer::getFromIdentifier(
    ptr<DBGSourceInfo> dbgInfo, const std::string identifier,
    std::vector<ptr<Expression::TypeRef>> generics, const std::string p_uuid) {

    // Transform the base first
    auto [item, success] = ctx->getItem(identifier);

    if (success) {
        if (item->isVal()) {
            // TODO: it should not be getValue, it should have it's own value
            auto val = item->getValue();
            return {val, std::nullopt, std::nullopt, std::nullopt,
                    std::nullopt};
        } else if (item->isFunc()) {
            return {std::nullopt, std::nullopt, item->getFunctions(),
                    std::nullopt, std::nullopt};
        } else if (item->isType()) {
            return {std::nullopt, item->getType(), std::nullopt, std::nullopt,
                    std::nullopt};
        } else if (item->isType()) {
            return {std::nullopt, item->getType(), std::nullopt, std::nullopt,
                    std::nullopt};
        } else if (item->isModule()) {
            return {std::nullopt, std::nullopt, std::nullopt, std::nullopt,
                    item->getModule()};
        } else {
            assert(false && "BUG: Unhandled value type!");
        }
    }

    auto uuid = p_uuid.empty() ? ctx->createIdentifierName(identifier, false)
                               : (p_uuid + "." + identifier);
    std::optional<std::vector<std::shared_ptr<ir::Func>>> funcs = std::nullopt;
    if (auto x = ctx->cache->getTransformedFunction(uuid)) {
        assert(x->get()->isFunc());
        funcs = x->get()->getFunctions();
    }

    if (auto t = ctx->cache->getType(uuid)) {
        auto ty = new Expression::TypeRef(identifier, dbgInfo, generics);
        return {std::nullopt,
                std::dynamic_pointer_cast<types::Type>(
                    transformClass(uuid, t.value(), ty)),
                std::nullopt, std::nullopt, std::nullopt};
    }

    std::optional<std::vector<cacheComponents::Functions::FunctionStore>>
        overloads = std::nullopt;
    if (auto x = ctx->cache->getFunction(uuid)) {
        overloads = x;
    }

    if (funcs || overloads) {
        return {std::nullopt, std::nullopt, funcs, overloads, std::nullopt};
    }

    return {std::nullopt, std::nullopt, std::nullopt, std::nullopt,
            std::nullopt};
}

} // namespace Syntax
} // namespace snowball