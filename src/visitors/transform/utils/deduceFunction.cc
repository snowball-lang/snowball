#include "../../Transformer.h"

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

namespace {
bool genericMatch(Expression::Param* generic, Expression::TypeRef* arg) {
  if (auto x = utils::cast<Expression::ReferenceType>(arg)) {
    return genericMatch(generic, x->getBaseType());
  } else if (auto x = utils::cast<Expression::PointerType>(arg)) {
    return genericMatch(generic, x->getBaseType());
  }

  return arg->getName() == generic->getName();
}

std::pair<types::Type*, int> matchedGeneric(Expression::Param* generic, types::Type* arg) {
  // We need to match with "genericMatch"
  // e.g. fn foo<T>(x: &T) T { x }
  //     foo(&1)
  //     T = i32
  int importance = 0;

  // Check if the generic is a reference type
  if (auto genericRefType = utils::cast<types::ReferenceType>(arg)) {
    if (generic->getType()->isReferenceType()) {
      // If both are reference types, match the pointed type
      return {genericRefType->getPointedType(), 2};
    } else {
      // If generic is a reference but arg is not, try matching the non-reference arg
      return {arg, 1};
    }
  }

  // Check if the generic is a pointer type
  if (auto genericPointerType = utils::cast<types::PointerType>(arg)) {
    if (generic->getType()->isPointerType()) {
      // If both are pointer types, match the pointed type
      return {genericPointerType->getPointedType(), 2};
    } else {
      // If generic is a pointer but arg is not, try matching the non-pointer arg
      return {arg, 1};
    }
  }

  // If the generic is neither a reference nor a pointer, return the argument as is
  return {arg, 0};
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
    const auto [deducedType, imp] = matchedGeneric(*it, arguments.at(argIdx));
    DUMP(arguments[argIdx]->getImpls().size())
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
      return {{}, FMT("Cannot deduce type '%s' in function call!", generic->getName().c_str()), -1};
    }
  }

  return {deducedTypes, "", importance};
}

} // namespace Syntax
} // namespace snowball