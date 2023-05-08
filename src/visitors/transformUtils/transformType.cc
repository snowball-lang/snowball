#include "../Transformer.h"

#include <memory>
#include <optional>

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

namespace {
Expression::Base* typeFromString(Expression::TypeRef *ty) {
    auto name = ty->getName();
    auto rfind = name.rfind("::");
    if (rfind != std::string::npos) {
        auto rightType = name.substr(rfind+2);
        auto leftType = name.substr(0, rfind);

        auto ident = Syntax::N<Expression::Identifier>(rightType);
        auto index = Syntax::N<Expression::Index>(typeFromString(Syntax::N<Expression::TypeRef>(leftType, ty->getDBGInfo())), ident, true);
        index->setDBGInfo(ty->getDBGInfo());
        return index;
    }

    auto ident = Syntax::N<Expression::Identifier>(ty->getName());
    ident->setDBGInfo(ty->getDBGInfo());
    return ident;
}
}

std::shared_ptr<types::Type>
Transformer::transformType(Expression::TypeRef *ty) {
    auto name          = ty->getPrettyName();
    auto id            = ty->getName();

    auto typeExpr = typeFromString(ty);

    {
        auto uuid = ctx->createIdentifierName(id, false);
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
        } if (auto x = ctx->cache->getType(uuid)) {
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
    }

    if (auto x = utils::cast<Expression::Identifier>(typeExpr)) {
        auto [_v, type, _o, _f, _m] = getFromIdentifier(x);
        std::string errorReason;
        if (_v.has_value()) {
            errorReason = "This is a value, not a type!";
        } else if (_o.has_value() || _f.has_value()) {
            errorReason = "This is a function, not a type!";
        } else if (_m.has_value()) {
            errorReason = "This is a module, not a type!";
        } else if (type.has_value()) {
            return *type;
        } else {
            E<VARIABLE_ERROR>(ty, FMT("Type '%s' not found!", name.c_str()));
        }

        E<TYPE_ERROR>(ty, FMT("Can't use '%s' as a type!", name.c_str()), errorReason);
    } else if (auto x = utils::cast<Expression::Index>(typeExpr)) {
        auto [_v, type, _o, _f, _m, canPrivate] = getFromIndex(ty->getDBGInfo(), x, true).first;

        std::string errorReason;
        if (_v.has_value()) {
            errorReason = "This is a value, not a type!";
        } else if (_o.has_value() || _f.has_value()) {
            errorReason = "This is a function, not a type!";
        } else if (_m.has_value()) {
            errorReason = "This is a module, not a type!";
        } else if (type.has_value()) {
            return *type;
        } else {
            E<VARIABLE_ERROR>(ty, FMT("Type '%s' not found!", name.c_str()));
        }

        E<TYPE_ERROR>(ty, FMT("Can't use '%s' as a type!", name.c_str()), errorReason);
    }

    if (ty->getGenerics().size() > 0) {
        E<TYPE_ERROR>(ty, "This type does not need to have generics!");
    }

    assert(false);
}

} // namespace Syntax
} // namespace snowball