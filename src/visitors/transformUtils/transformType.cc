#include "../../ast/syntax/common.h"
#include "../../ast/types/PointerType.h"
#include "../../utils/utils.h"
#include "../Transformer.h"

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

    std::shared_ptr<types::Type> returnedType = nullptr;

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
            returnedType = *type;
            goto continueTypeFetch;
        } else {
            goto continueTypeFetch;
        }

        E<TYPE_ERROR>(ty, FMT("Can't use '%s' as a type!", name.c_str()),
                      {.info = errorReason});
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
            returnedType = *type;
            goto continueTypeFetch;
        } else {
            goto continueTypeFetch;
        }

        E<TYPE_ERROR>(ty, FMT("Can't use '%s' as a type!", name.c_str()),
                {.info = errorReason});
    }

  continueTypeFetch:
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
            for (auto t : x.value()) {
                assert(t->isType());
                auto transformed = t->getType();
                assert(t != nullptr);

                if (typeGenericsMatch(ty, transformed)) {
                    return transformed;
                }
            }
        }

        if (auto x = ctx->cache->getType(uuid)) {
            auto cls = *x;

            Statement::GenericContainer<>::GenericList generics;
            // TODO: check if there's another way to avoid repetition of code

            if (auto c = utils::cast<Statement::ClassDef>(cls.type)) {
                generics = c->getGenerics();
            } else if (auto c = utils::cast<Statement::TypeAlias>(cls.type)) {
                generics = c->getGenerics();
            } else {
                assert(false);
            }

            auto requiredArguments = 0;
            for (auto arg : generics) {
                // Check for if there's no default type
                if (arg->type == nullptr) {
                    requiredArguments++;
                }
            }

            // TODO: check for default generic types
            if (ty->getGenerics().size() < requiredArguments) {
                E<TYPE_ERROR>(ty, FMT("Type '%s' require to have %i generic "
                                      "argument(s) but %i where given!",
                                      name.c_str(), requiredArguments,
                                      ty->getGenerics().size()));
            }

            return transformTypeFromBase(uuid, cls, ty);
        }
    }

    if (returnedType == nullptr) {
        E<VARIABLE_ERROR>(ty, FMT("Type '%s' not found!", name.c_str()));
    }
    
    return returnedType;
}

} // namespace Syntax
} // namespace snowball