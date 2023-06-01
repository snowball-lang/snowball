#include "../Transformer.h"
#include "../../ast/types/PointerType.h"

#include <memory>
#include <optional>

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

std::shared_ptr<types::Type>
Transformer::transformType(Expression::TypeRef *ty) {

    auto name = ty->getPrettyName();
    auto id   = ty->getName();

    if (auto x = transformSpecialType(ty)) {
        return x;
    }

    if (auto x = ty->_getInternalType()) {
        return x;
    }

    if (ty->isTypeDecl()) {
        auto decl = utils::cast<Expression::DeclType>(ty);
        assert(decl);

        decl->getExpr()->accept(this);
        return this->value->getType();
    }

    if (ty->isPointerType()) {
        auto pointer = utils::cast<Expression::PointerType>(ty);
        assert(pointer);

        // return ;
        return transformType(pointer->getBaseType())->getPointerTo();
    }

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
        }
        if (auto x = ctx->cache->getType(uuid)) {
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

    auto ast = ty->_getInternalAST();

    if (ast == nullptr) {
        if (ty->getGenerics().size() > 0) {
            ast = Syntax::N<Expression::GenericIdentifier>(ty->getName(),
                                                           ty->getGenerics());
        } else {
            ast = Syntax::N<Expression::Identifier>(ty->getName());
        }
        ast->setDBGInfo(ty->getDBGInfo());
    }

    if (auto x = utils::cast<Expression::Identifier>(ast)) {
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

        E<TYPE_ERROR>(ty, FMT("Can't use '%s' as a type!", name.c_str()),
                      errorReason);
    } else if (auto x = utils::cast<Expression::Index>(ast)) {
        auto [_v, type, _o, _f, _m, canPrivate] =
            getFromIndex(ty->getDBGInfo(), x, true).first;

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

        E<TYPE_ERROR>(ty, FMT("Can't use '%s' as a type!", name.c_str()),
                      errorReason);
    }

    assert(false);
}

} // namespace Syntax
} // namespace snowball