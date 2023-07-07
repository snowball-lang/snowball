
#include "../Transformer.h"

#include <optional>

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

Transformer::StoreType Transformer::getFromIdentifier(Expression::Identifier* s) {
    auto g = utils::cast<Expression::GenericIdentifier>(s);
    auto generics = (g != nullptr) ? g->getGenerics() : std::vector<Expression::TypeRef*>{};
    return getFromIdentifier(s->getDBGInfo(), s->getIdentifier(), generics);
}
Transformer::StoreType Transformer::getFromIdentifier(DBGSourceInfo* dbgInfo,
                                                      const std::string identifier,
                                                      std::vector<Expression::TypeRef*>
                                                              generics,
                                                      const std::string p_uuid) {
    // Transform the base first
    auto [item, success] = ctx->getItem(identifier);

    if (success) {
        if (item->isVal()) {
            // TODO: it should not be getValue, it should have it's own
            // value
            auto val = item->getValue();
            return {val, std::nullopt, std::nullopt, std::nullopt, std::nullopt};
        } else if (item->isFunc()) {
            return {std::nullopt, std::nullopt, item->getFunctions(), std::nullopt, std::nullopt};
        } else if (item->isType()) {
            return {std::nullopt, item->getType(), std::nullopt, std::nullopt, std::nullopt};
        } else if (item->isType()) {
            return {std::nullopt, item->getType(), std::nullopt, std::nullopt, std::nullopt};
        } else if (item->isModule()) {
            return {std::nullopt, std::nullopt, std::nullopt, std::nullopt, item->getModule()};
        } else {
            assert(false && "BUG: Unhandled value type!");
        }
    }
    int uuidStackIndex = -1;
    std::string uuidStackOverride = "";
fetchFromUUID:
    // If we can't find it in the stack, we need to fetch it from the cache
    auto uuid = uuidStackOverride.empty() ? p_uuid.empty()
                    ? ctx->createIdentifierName(identifier, false)
                    : (p_uuid + "." + identifier)
                                          : (uuidStackOverride + "." + identifier);
    std::optional<std::deque<std::shared_ptr<ir::Func>>> funcs = std::nullopt;
    if (auto x = ctx->cache->getTransformedFunction(uuid)) {
        assert(x->get()->isFunc());
        funcs = x->get()->getFunctions();
    }
    if (auto x = ctx->cache->getTransformedType(uuid)) {
        auto ty = new Expression::TypeRef(identifier, dbgInfo, generics);
        std::shared_ptr<types::Type> lastType = nullptr;
        for (auto t : x.value()) {
            assert(t->isType());
            auto transformed = std::dynamic_pointer_cast<types::DefinedType>(t->getType());
            assert(t != nullptr);
            if (typeGenericsMatch(ty, transformed)) {
                return {std::nullopt, transformed, std::nullopt, std::nullopt, std::nullopt};
            }
        }
    }
    if (auto t = ctx->cache->getType(uuid)) {
        auto ty = new Expression::TypeRef(identifier, dbgInfo, generics);
        return {std::nullopt, transformTypeFromBase(uuid, t.value(), ty), std::nullopt,
                std::nullopt, std::nullopt};
    }
    
    std::optional<std::vector<cacheComponents::Functions::FunctionStore>> overloads = std::nullopt;
    if (auto x = ctx->cache->getFunction(uuid)) { overloads = x; }
    if (funcs || overloads) { return {std::nullopt, std::nullopt, funcs, overloads, std::nullopt}; }
    if (auto mod = ctx->cache->getModule(uuid)) {
        return {std::nullopt, std::nullopt, std::nullopt, std::nullopt, mod};
    }
    if (uuidStackIndex + 1 < ctx->uuidStack.size()) {
        uuidStackIndex++;
        uuidStackOverride = ctx->uuidStack[uuidStackIndex];
        goto fetchFromUUID;
    }

    return {std::nullopt, std::nullopt, std::nullopt, std::nullopt, std::nullopt};
}

} // namespace Syntax
} // namespace snowball