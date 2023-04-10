#include "../Transformer.h"

#include <memory>

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

std::shared_ptr<types::Type>
Transformer::transformType(Expression::TypeRef* ty) {
    auto name          = ty->getPrettyName();
    auto [item, found] = ctx->getItem(name);
    if (!found) {
        auto uuid = ctx->createIdentifierName(name, false);
        if (auto x = ctx->cache->getTransformedType(uuid)) {
            std::shared_ptr<types::Type> lastType = nullptr;
            for (auto t : x.value()) {
                assert(t->isType());
                auto transformed =
                    std::dynamic_pointer_cast<types::DefinedType>(t->getType());
                assert(t != nullptr);
                if (typeGenericsMatch(ty, transformed)) {
                    return transformed;
                }
            }
        } else if (auto x = ctx->cache->getType(uuid)) {
            auto cls = *x;

            // TODO: check for default generic types
            if (cls.type->getGenerics().size() != ty->getGenerics().size()) {
                E<TYPE_ERROR>(ty,
                              FMT("Type '%s' require to have %i generic "
                                  "arguments but %i where given!",
                                  name.c_str(), cls.type->getGenerics().size(),
                                  ty->getGenerics().size()));
            }

            return transformClass(uuid, cls, ty);
        }

        E<VARIABLE_ERROR>(ty, FMT("Type '%s' not found!", name.c_str()));
    } else if (!item->isType()) {
        E<TYPE_ERROR>(ty, FMT("Value '%s' is not a type!", name.c_str()));
    }

    if (ty->getGenerics().size() > 0) {
        E<TYPE_ERROR>(ty, "This type does not need to have generics!");
    }

    return item->getType();
}

} // namespace Syntax
} // namespace snowball