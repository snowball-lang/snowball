#include "../../../ast/syntax/common.h"
#include "../../../ast/types/ReferenceType.h"
#include "../../../utils/utils.h"
#include "../../Transformer.h"

#include <memory>
#include <optional>

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

template <typename T>
using GenericContainer = snowball::Syntax::Statement::GenericContainer<T>;

namespace snowball {
namespace Syntax {

types::Type* Transformer::transformType(Expression::TypeRef* ty) {
  if (ty->isMutable() && ty->getName() != _SNOWBALL_MUT_PTR && !ty->isPointerType()) {
    ty->setMutable(false); // stop infinite loops
    auto x = transformType(ty);
    ty->setMutable(true);
    x->setMutable(true);
    return x;
  }

  int uuidStackIndex = -1;
  std::string uuidStackOverride = "";

  if (ty->isReferenceType()) {
    auto pointer = utils::cast<Expression::ReferenceType>(ty);
    assert(pointer);
    auto x = transformType(pointer->getBaseType())->getReferenceTo();
    return x;
  } else if (ty->isPointerType()) {
    auto pointer = utils::cast<Expression::PointerType>(ty);
    assert(pointer);
    auto baseType = transformType(pointer->getBaseType());
    auto x = baseType->getPointerTo(pointer->isMutable());
    auto typeRef =
            TR(pointer->isMutable() ? _SNOWBALL_MUT_PTR : _SNOWBALL_CONST_PTR,
               nullptr,
               std::vector<Expression::TypeRef*>{baseType->toRef()});
    transformType(typeRef);
    return x;
  } else if (ty->isTypeDecl()) {
    auto decl = utils::cast<Expression::DeclType>(ty);
    assert(decl);

    auto val = trans(decl->getExpr());
    return val->getType()->copy();
  } else if (ty->isFunctionType()) {
    auto fn = utils::cast<Expression::FuncType>(ty);
    assert(fn);
    std::vector<types::Type*> args;
    for (auto arg : fn->getArgs()) args.push_back(transformType(arg));
    auto ret = transformType(fn->getReturnValue());
    auto ty = getBuilder().createFunctionType(args, ret);
    ty->addImpl(ctx->getBuiltinTypeImpl("Sized"));
    return ty;
  } else if (auto x = ty->_getInternalType()) {
    // TODO: maybe move up in the function to prevent problems with generics?
    return x->copy();
  } else if (auto x = transformSpecialType(ty)) {
    if (utils::is<types::NumericType>(x) && !utils::is<types::CharType>(x)) {
      // we create a new instance of the type so we can access it's methods and operators
      // we create a new instance of "IntegerImpl<T>"
      auto typeRef = TR(_SNOWBALL_INT_IMPL, ty->getDBGInfo(), std::vector<Expression::TypeRef*>{x->toRef()});
      transformType(typeRef);
    }
    return x;
  }

  auto name = ty->getPrettyName();
  auto id = ty->getId();
  if (id.empty()) { id = ty->getName(); }
  types::Type* returnedType = nullptr;
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

    E<TYPE_ERROR>(ty, FMT("Cant use '%s' as a type!", name.c_str()), {.info = errorReason});
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
      if (auto x = utils::cast<types::BaseType>(type.value()); x && x->isPrivate() && !canPrivate) {
        E<TYPE_ERROR>(
                ty,
                FMT("Cant use '%s' as a type!", name.c_str()),
                {.info = "This is a private type and you can't access it from here!",
                 .note = "Private types can only be accessed from inside the "
                         "module they are defined in.",
                 .help = "If you are trying to access a private type from "
                         "outside the module, you can't\ndo that. "
                         "If you are trying to access a private type from "
                         "inside the module, \nyou can't do that either. "
                         "You can only access private types from inside "
                         "the\nmodule they are defined in."}
        );
      }

      returnedType = *type;
      goto continueTypeFetch;
    } else {
      goto continueTypeFetch;
    }

    E<TYPE_ERROR>(ty, FMT("Cant use '%s' as a type!", name.c_str()), {.info = errorReason});
  }

continueTypeFetch:
  // If we can't find it in the stack, we need to fetch it from the cache
  auto uuid = uuidStackOverride.empty() ? ctx->createIdentifierName(id, false) : (uuidStackOverride + "." + id);
  bool existsWithGenerics = false;

  if (auto x = ctx->cache->getTransformedType(uuid)) {
    existsWithGenerics = true;
    for (auto t : x.value()) {
      assert(t->isType());
      auto transformed = t->getType();
      assert(t != nullptr);
      if (typeGenericsMatch(ty, transformed)) {
        if (auto alias = utils::cast<types::TypeAlias>(transformed)) { transformed = alias->getBaseType(); }

        return transformed->copy();
      }
    }
  }

  if (auto x = ctx->cache->getType(uuid)) {
    auto cls = *x;
    auto transformed = transformTypeFromBase(uuid, cls, ty);
    if (auto alias = utils::cast<types::TypeAlias>(transformed)) { transformed = alias->getBaseType(); }
    return transformed->copy();
  }

  if (existsWithGenerics) {
    E<TYPE_ERROR>(
            ty,
            FMT("Type '%s' requires to have no template "
                "parameters but at least one has been given?",
                name.c_str())
    );
  }

  if (returnedType == nullptr) {
    if (uuidStackIndex + 1 < ctx->uuidStack.size()) {
      uuidStackIndex++;
      uuidStackOverride = ctx->uuidStack[uuidStackIndex];
      goto continueTypeFetch;
    }

    E<VARIABLE_ERROR>(ty, FMT("Type '%s' not found from the current context!", name.c_str()));
  }

  // TODO: did we ever needed this?!?!?
  // if (!typeGenericsMatch(ty, returnedType)) {
  //  auto compAsDefinedType = utils::cast<GenericContainer<types::Type*>>(returnedType);
  //  auto compGenerics = compAsDefinedType == nullptr ? std::vector<types::Type*>{} : compAsDefinedType->getGenerics();
  //  typeGenericsMatch(ty, returnedType);
  //  E<TYPE_ERROR>(
  //          ty,
  //          FMT("Type generics for '%s' dont match with '%s's generics!",
  //              returnedType->getPrettyName().c_str(),
  //              ty->getPrettyName().c_str())
  //  );
  //}

  if (auto alias = utils::cast<types::TypeAlias>(returnedType)) { returnedType = alias->getBaseType(); }

  return returnedType->copy();
}

} // namespace Syntax
} // namespace snowball