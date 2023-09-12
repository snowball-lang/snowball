
#include "../../Transformer.h"

#include <cmath>
#include <algorithm>

#include <llvm/IR/Attributes.h>

#define STYPE_INSTANCE(x) if (n == x)
#define ASSERT_GENERICS(n, t)                                                                                          \
  auto generics = ty->getGenerics();                                                                                   \
  if (generics.size() != n) {                                                                                          \
    E<TYPE_ERROR>(ty->getDBGInfo(),                                                                                    \
            FMT("Expected '%i' generics for '%s' but got '%i' instead", n, t.c_str(), generics.size()));               \
  }

namespace snowball {
namespace Syntax {

inline const std::string FUNCTION_RETURN_STYPE = "Core::ReturnType";
inline const std::string SIZED_TYPE_CHECK_STYPE = "Core::Sized";
inline const std::string IS_NUMERIC_CHECK_STYPE = "Core::IsNumeric";
inline const std::string IS_POINTER_CHECK_STYPE = "Core::IsPointer";
inline const std::string CASTABLE_TO_CHECK_STYPE = "Core::CastableTo";
inline const std::string IMPLEMENTS_CHECK_STYPE = "Core::Implements";
inline const std::string REMOVE_REFERENCES_STYPE = "Core::RemoveReferences";

types::Type* Transformer::transformSpecialType(Expression::TypeRef* ty) {
  auto n = ty->getName();

  // here's where we get all "i[N]" and "f[N]" types and we validate the size
  if (n == "bool") {
    return new types::IntType(1);
  } else if (utils::startsWith(n, "i")) {
    auto bitsString = n.substr(1);
    if (bitsString.empty() || !std::isdigit(bitsString[0])) return nullptr;
    if (!std::all_of(bitsString.begin(), bitsString.end(), ::isdigit)) {
      E<TYPE_ERROR>(ty,
              FMT("Integer type '%s' is expected to be in the form of 'i[N]' where N is a number but "
                  "found '%s' instead.",
                      n.c_str(), bitsString.c_str()));
    }
    auto bits = std::stoi(bitsString);
    // The number of bits must be from 1 to 2^23 (8,388,608)
    // we asume it's greater than 0 a negative number would end in a syntax error
    if (bits < 1 || bits > pow(2, 23)) {
      E<TYPE_ERROR>(ty,
              FMT("Integer type '%s' is expected to be in the form of 'i[N]' where N is a number "
                  "between 1 and 2^23 (8,388,608) but found '%s' instead.",
                      n.c_str(), bitsString.c_str()));
    }
    switch (bits) {
      case 1:
        E<TYPE_ERROR>(ty,
                FMT("If you want a boolean type, use 'bool' instead of 'i1'!"), {
          .note = FMT("This is used used for consistency with other languages.")
        });
      default:
        return new types::IntType(bits);
    }
  } else if (utils::startsWith(n, "f")) {
    auto bitsString = n.substr(1);
    if (bitsString.empty() || !std::isdigit(bitsString[0])) return nullptr;
    if (!std::all_of(bitsString.begin(), bitsString.end(), ::isdigit)) {
      E<TYPE_ERROR>(ty,
              FMT("Float type '%s' is expected to be in the form of 'f[N]' where N is a number but "
                  "found '%s' instead.",
                      n.c_str(), bitsString.c_str()));
    }
    auto bits = std::stoi(bitsString);
    // The number of bits must be 16, 32 or 64
    if (bits != 16 && bits != 32 && bits != 64) {
      E<TYPE_ERROR>(ty,
              FMT("Float type '%s' is expected to be in the form of 'f[N]' where N is 16, 32 or 64 "
                  "but found '%s' instead.",
                      n.c_str(), bitsString.c_str()));
    }
    return new types::FloatType(bits);
  }

  STYPE_INSTANCE(REMOVE_REFERENCES_STYPE) {
    ASSERT_GENERICS(1, REMOVE_REFERENCES_STYPE)
    auto generic = generics.at(0);
    auto type = transformType(generic);
    if (auto ref = utils::cast<types::ReferenceType>(type)) 
      { return ref->getPointedType(); }
    return type;
  }

  STYPE_INSTANCE(FUNCTION_RETURN_STYPE) {
    ASSERT_GENERICS(1, FUNCTION_RETURN_STYPE)
    auto generic = generics.at(0);
    auto type = transformType(generic);
    auto fnType = utils::cast<types::FunctionType>(type);
    if (fnType) { return fnType->getRetType(); }
    E<TYPE_ERROR>(ty,
            FMT("Type '%i' expected first generic parameter to "
                "be a function but it found type '%s'.",
                    FUNCTION_RETURN_STYPE.c_str(),
                    type->getPrettyName().c_str()));
  }

  STYPE_INSTANCE(SIZED_TYPE_CHECK_STYPE) {
    ASSERT_GENERICS(1, SIZED_TYPE_CHECK_STYPE)
    auto generic = generics.at(0);
    auto type = transformType(generic);
    // TODO: check for other instances
    if (utils::cast<types::VoidType>(type)) {
      E<TYPE_ERROR>(ty,
              FMT("Type '%s' is expected to contain a known size at compile time but "
                  "found '%s'.",
                      SIZED_TYPE_CHECK_STYPE.c_str(),
                      type->getPrettyName().c_str()),
              ErrorInfo{
                      // TODO: instead of showing the call, show somthing like (for all
                      // the errors here and some generic related errors):
                      //  typeGenerationBacktrace.at(1)
                      //.tail = ctx->createErrorTail(ctx->latestCall)
              });
    }
    return type;
  }

  STYPE_INSTANCE(IS_NUMERIC_CHECK_STYPE) {
    ASSERT_GENERICS(1, IS_NUMERIC_CHECK_STYPE)
    auto generic = generics.at(0);
    auto type = transformType(generic);
    // TODO: check for other instances
    if (auto x = utils::cast<types::PrimitiveType>(type); !((x == nullptr) || types::NumericType::isNumericType(x))) {
      E<TYPE_ERROR>(ty,
              FMT("Type '%s' is expected to be a numeric type but found '%s'!", IS_NUMERIC_CHECK_STYPE.c_str(),
                      type->getPrettyName().c_str()));
    }
    return type;
  }

  STYPE_INSTANCE(IS_POINTER_CHECK_STYPE) {
    ASSERT_GENERICS(1, IS_POINTER_CHECK_STYPE)
    auto generic = generics.at(0);
    auto type = transformType(generic);
    // TODO: check for other instances
    if (!utils::cast<types::ReferenceType>(type)) {
      E<TYPE_ERROR>(ty,
              FMT("Type '%s' is expected to contain a pointer type but found '%s'.",
                      IS_POINTER_CHECK_STYPE.c_str(),
                      type->getPrettyName().c_str()),
              ErrorInfo{
                      // TODO: instead of showing the call, show somthing like (for all
                      // the errors here and some generic related errors):
                      //  typeGenerationBacktrace.at(1)
                      //.tail = ctx->createErrorTail(ctx->latestCall)
              });
    }
    return type;
  }

  STYPE_INSTANCE(CASTABLE_TO_CHECK_STYPE) {
    ASSERT_GENERICS(2, CASTABLE_TO_CHECK_STYPE)

    auto child = generics.at(0);
    auto parent = generics.at(1);

    auto childType = transformType(child);
    auto parentType = transformType(parent);

    // TODO: check for other instances
    if (!childType->canCast(parentType)) {
      E<TYPE_ERROR>(ty,
              FMT("Type '%s' expected type '%s' to be able to cast to '%s' but it can't!",
                      CASTABLE_TO_CHECK_STYPE.c_str(), childType->getPrettyName().c_str(),
                      parentType->getPrettyName().c_str()));
    }

    return childType;
  }

  STYPE_INSTANCE(IMPLEMENTS_CHECK_STYPE) {
    ASSERT_GENERICS(2, IMPLEMENTS_CHECK_STYPE)

    auto child = generics.at(0);
    auto parent = generics.at(1);

    auto childType = transformType(child);
    auto parentType = transformType(parent);

    auto definedType = utils::cast<types::DefinedType>(childType);
    if (!definedType || !definedType->hasParent() || !definedType->getParent()->is(parentType)) {
      E<TYPE_ERROR>(ty,
              FMT("Type '%s' expected type '%s' to be a subtype of '%s' but it isn't!", IMPLEMENTS_CHECK_STYPE.c_str(),
                      childType->getPrettyName().c_str(), parentType->getPrettyName().c_str()));
    }

    return childType;
  }

  return nullptr;
}

} // namespace Syntax
} // namespace snowball
