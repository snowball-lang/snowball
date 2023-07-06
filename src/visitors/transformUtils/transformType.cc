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

std::shared_ptr<types::Type> Transformer::transformType(Expression::TypeRef* ty) {
    auto name = ty->getPrettyName();
    auto id = ty->getName();
    std::shared_ptr<types::Type> returnedType = nullptr;
    if (auto x = transformSpecialType(ty)) { return x; }
    auto ast = ty->_getInternalAST();
    if (ast == nullptr) {
        if (ty->getGenerics().size() > 0) {
            ast = Syntax::N<Expression::GenericIdentifier>(ty->getName(), ty->getGenerics());
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

        E<TYPE_ERROR>(ty, FMT("Can't use '%s' as a type!", name.c_str()), {.info = errorReason});
    } else if (auto x = utils::cast<Expression::Index>(ast)) {
        auto [_v, type, _o, _f, _m, canPrivate] = getFromIndex(ty->getDBGInfo(), x, true).first;

        std::string errorReason;
        if (_v.has_value()) {
            errorReason = "This is a value, not a type!";
        } else if (_o.has_value() || _f.has_value()) {
            errorReason = "This is a function, not a type!";
        } else if (_m.has_value()) {
            errorReason = "This is a module, not a type!";
        } else if (type.has_value()) {
            if (auto x = utils::dyn_cast<types::DefinedType>(type.value());
                x && x->isPrivate() && !canPrivate) {
                E<TYPE_ERROR>(ty,
                              FMT("Can't use '%s' as a type!", name.c_str()),
                              {.info = "This is a private type and you can't access it from here!",
                               .note = "Private types can only be accessed from inside the "
                                       "module they are defined in.",
                               .help = "If you are trying to access a private type from "
                                       "outside the module, you can't\ndo that. "
                                       "If you are trying to access a private type from "
                                       "inside the module, \nyou can't do that either. "
                                       "You can only access private types from inside "
                                       "the\nmodule they are defined in."});
            }

            returnedType = *type;
            goto continueTypeFetch;
        } else {
            goto continueTypeFetch;
        }

        E<TYPE_ERROR>(ty, FMT("Can't use '%s' as a type!", name.c_str()), {.info = errorReason});
    }

continueTypeFetch:
    // TODO: maybe move up in the function to prevent problems with generics?
    if (auto x = ty->_getInternalType()) { return x; }

    if (ty->isTypeDecl()) {
        auto decl = utils::cast<Expression::DeclType>(ty);
        assert(decl);

        decl->getExpr()->accept(this);
        return this->value->getType();
    }

    if (ty->isPointerType()) {
        auto pointer = utils::cast<Expression::PointerType>(ty);
        assert(pointer);

        return transformType(pointer->getBaseType())->getPointerTo();
    }

    auto uuid = ctx->createIdentifierName(id, false);
    bool existsWithGenerics = false;

    if (auto x = ctx->cache->getTransformedType(uuid)) {
        existsWithGenerics = true;
        for (auto t : x.value()) {
            assert(t->isType());
            auto transformed = t->getType();
            assert(t != nullptr);
            if (typeGenericsMatch(ty, transformed)) { return transformed; }
        }
    }

    if (auto x = ctx->cache->getType(uuid)) {
        auto cls = *x;
        return transformTypeFromBase(uuid, cls, ty);
    }

    if (existsWithGenerics) {
        E<TYPE_ERROR>(ty,
                      FMT("Type '%s' requires to have no template "
                          "parameters but at least one has been given?",
                          name.c_str()));
    }

    if (returnedType == nullptr) E<VARIABLE_ERROR>(ty, FMT("Type '%s' not found!", name.c_str()));
    if (!typeGenericsMatch(ty, returnedType)) {
        auto compAsDefinedType = utils::dyn_cast<types::DefinedType>(returnedType);
        auto compGenerics = compAsDefinedType == nullptr
                ? std::vector<std::shared_ptr<types::Type>>{}
                : compAsDefinedType->getGenerics();
        E<TYPE_ERROR>(ty,
                      FMT("Type '%s' require to have %i generic "
                          "argument(s) but %i where given!",
                          returnedType->getPrettyName().c_str(),
                          compGenerics.size(),
                          ty->getGenerics().size()));
    }
    return returnedType;
}

} // namespace Syntax
} // namespace snowball