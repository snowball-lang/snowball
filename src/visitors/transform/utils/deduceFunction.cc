#include "../../Transformer.h"

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

namespace {
bool genericMatch(Expression::Param* generic, Expression::TypeRef* arg) {
  if (auto x = utils::cast<Expression::ReferenceType>(arg)) {
    return x->getBaseType()->getName() == generic->getName();
  } else if (auto x = utils::cast<Expression::PointerType>(arg)) {
    return x->getBaseType()->getName() == generic->getName();
  }

  auto exists = arg->getName() == generic->getName();
  if (!exists && arg->getGenerics().size() > 0) {
    auto generics = arg->getGenerics();
    exists = std::any_of(generics.begin(), generics.end(), [&](auto& g) {
      return genericMatch(generic, g);
    });
  }

// ----- FOR A LONG DISTANCED FUTURE: AUTO DEDUCE FUNCTION TYPES
//  if (!exists && utils::is<Expression::FuncType>(arg)) {
//    auto funcType = utils::cast<Expression::FuncType>(arg);
//    auto args = funcType->getArgs();
//    exists = std::any_of(args.begin(), args.end(), [&](auto& a) {
//      return genericMatch(generic, a);
//    });
//    if (!exists) {
//      exists = genericMatch(generic, funcType->getReturnValue());
//    }
//  }
/// -----

  return exists;
}

std::pair<types::Type*, int> matchedGeneric(Expression::Param* generic, types::Type* arg, Expression::Param* genericParam) {
  // We need to match with "genericMatch"
  // e.g. fn foo<T>(x: &T) T { x }
  //     foo(&1)
  //     T = i32

  // Check if the generic is a reference type
  if (auto genericRefType = utils::cast<types::ReferenceType>(arg)) {
    if (generic->getType()->isReferenceType()) {
      // If both are reference types, match the pointed type
      return {genericRefType->getPointedType(), 3};
    }
  }

  // Check if the generic is a pointer type
  if (auto genericPointerType = utils::cast<types::PointerType>(arg)) {
    if (generic->getType()->isPointerType()) {
      // If both are pointer types, match the pointed type
      return {genericPointerType->getPointedType(), 3};
    }
  }

  if (auto genericRefType = utils::cast<types::BaseType>(arg)) {
    if (genericRefType->isGeneric()) {
      int indexExists = -1;
      auto generics = genericRefType->getGenerics();
      auto argGenerics = generic->getType()->getGenerics();
      if (generics.size() < argGenerics.size()) return {arg, 1};
      for (int i = 0; i < argGenerics.size(); i++) {
        if (genericMatch(genericParam, argGenerics[i])) {
          indexExists = i;
          break;
        }
      }
      if (indexExists != -1) {
        return {matchedGeneric(generic, generics[indexExists], genericParam).first, 3};
      }
    }
  }

// ----- FOR A LONG DISTANCED FUTURE: AUTO DEDUCE FUNCTION TYPES
//  if (auto genericRefType = utils::cast<types::FunctionType>(arg)) {
//    bool match = false;
//    auto args = genericRefType->getArgs();
//    DUMP_S(genericRefType->getPrettyName().c_str())
//    auto fn = utils::cast<Expression::FuncType>(generic->getType());
//    if (!fn) return {arg, 1};
//    auto fnArgs = fn->getArgs();
//    for (int i = 0; i < args.size(); i++) {
//      if (genericMatch(genericParam, args[i]->toRef())) {
//        match = true;
//        auto [deducedType, imp] = matchedGeneric(generic, fnArgs[i], genericParam);
//        if (deducedType != nullptr) {
//          return {matchedGeneric(generic, fnArgs[i], genericParam).first, 3};
//        }
//      }
//    }
//    if (!match) {
//      if (genericMatch(genericParam, fn->getReturnValue())) {
//        return {matchedGeneric(generic, genericRefType->getRetType(), genericParam).first, 3};
//      }
//    }
//  }
/// -----

  // If the generic is neither a reference nor a pointer, return the argument as is
  return {arg, 1};
}

#undef HANDLE_POINTER
} // namespace

std::pair<std::optional<types::Type*>, int> Transformer::deduceFunctionType(
        Expression::Param* generic,
        const std::vector<Expression::Param*>& fnArgs,
        const std::vector<types::Type*>& arguments,
        const std::vector<types::Type*>& generics,
        const std::vector<types::Type*>& deducedTypes
) {
  // I'm pretty sure this function works, but I'm a programmer, not a
  // magician.

  // See if a generic parameter was given
  const auto genericsSize = generics.size();
  if (genericsSize > deducedTypes.size()) {
    const auto index = deducedTypes.size();
    return {generics[index], 1};
  }

  // Check if the generic is used inside the variables
  const auto it = std::find_if(fnArgs.begin(), fnArgs.end(), [&](const auto& arg) {
    return genericMatch(generic, arg->getType());
  });

  if (it != fnArgs.end()) {
    const auto argIdx = std::distance(fnArgs.begin(), it);
    const auto [deducedType, imp] = matchedGeneric(*it, arguments.at(argIdx), generic);
    return {deducedType, imp};
  }

  // Check if the generic has a default type and non was found
  if (generic->type != nullptr) { return {transformType(generic->type), 0}; }

  return {std::nullopt, -1};
}

std::tuple<std::vector<types::Type*>, std::string, int> Transformer::deduceFunction(
        cacheComponents::Functions::FunctionStore s,
        const std::vector<types::Type*>& arguments,
        const std::vector<types::Type*>& generics
) {
  auto function = s.function;
  auto fnArgs = function->getArgs();

  std::vector<types::Type*> deducedTypes;
  int importance = 0;

  for (const auto& generic : function->getGenerics()) {
    const auto [deducedType, imp] = deduceFunctionType(generic, fnArgs, arguments, generics, deducedTypes);
    if (deducedType.has_value()) {
      deducedTypes.push_back(deducedType.value());
      importance += imp;
    } else {
      return {{}, FMT("Coudn`t deduce type '%s' in function call!", generic->getName().c_str()), -1};
    }
  }

  return {deducedTypes, "", importance};
}

} // namespace Syntax
} // namespace snowball