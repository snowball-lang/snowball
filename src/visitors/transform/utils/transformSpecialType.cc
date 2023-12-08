
#include "../../Transformer.h"

#include <algorithm>
#include <cmath>

#include <llvm/IR/Attributes.h>

#define STYPE_INSTANCE(x) if (n == x)
#define ASSERT_GENERICS(n, t)                                                                                          \
  auto generics = ty->getGenerics();                                                                                   \
  if (generics.size() != n) {                                                                                          \
    E<TYPE_ERROR>(                                                                                                     \
            ty->getDBGInfo(),                                                                                          \
            FMT("Expected '%i' generic(s) for '%s' but got '%i' instead", n, t.c_str(), generics.size())               \
    );                                                                                                                 \
  }

namespace snowball {
namespace Syntax {

inline const std::string FUNCTION_RETURN_STYPE = "Std::ReturnType";
inline const std::string REMOVE_REFERENCES_STYPE = "Std::RemoveReferences";

types::Type* Transformer::transformSpecialType(Expression::TypeRef* ty) {
  auto n = ty->getName();

  // here's where we get all "i[N]" and "f[N]" types and we validate the size
  if (n == "bool") {
    return ctx->getPrimitiveNumberType<types::IntType>(1);
  } else if (utils::startsWith(n, "i") || utils::startsWith(n, "u")) {
    bool isSigned = utils::startsWith(n, "i");
    auto bitsString = n.substr(1);
    if (bitsString.empty() || !std::isdigit(bitsString[0])) return nullptr;
    if (!std::all_of(bitsString.begin(), bitsString.end(), ::isdigit)) {
      E<TYPE_ERROR>(
              ty,
              FMT("Integer type '%s' is expected to be in the form of 'i[N]' where N is a number but "
                  "found '%s' instead.",
                  n.c_str(),
                  bitsString.c_str())
      );
    }
    auto bits = std::stoi(bitsString); // TODO: check if it's a digit
    // The number of bits must be from 1 to 2^23 (8,388,608)
    // we asume it's greater than 0 a negative number would end in a syntax error
    if (bits < 1 || bits > SN_INT_MAX_POWER) {
      E<TYPE_ERROR>(
              ty,
              FMT("Integer type '%s' is expected to be in the form of 'i[N]' where N is a number "
                  "between 1 and 2^23 (8,388,608) but found '%s' instead.",
                  n.c_str(),
                  bitsString.c_str())
      );
    }
    switch (bits) {
      case 1:
        E<TYPE_ERROR>(
                ty,
                FMT("If you want a boolean type, use 'bool' instead of 'i1'!"),
                {.note = FMT("This is used used for consistency with other languages.")}
        );
      default: {
        return ctx->getPrimitiveNumberType<types::IntType>(bits, isSigned);
      }
    }
  } else if (utils::startsWith(n, "f")) {
    auto bitsString = n.substr(1);
    if (bitsString.empty() || !std::isdigit(bitsString[0])) return nullptr;
    if (!std::all_of(bitsString.begin(), bitsString.end(), ::isdigit)) {
      E<TYPE_ERROR>(
              ty,
              FMT("Float type '%s' is expected to be in the form of 'f[N]' where N is a number but "
                  "found '%s' instead.",
                  n.c_str(),
                  bitsString.c_str())
      );
    }
    auto bits = std::stoi(bitsString); // TODO: check if it's a digit
    // The number of bits must be 16, 32 or 64
    if (bits != 16 && bits != 32 && bits != 64) {
      E<TYPE_ERROR>(
              ty,
              FMT("Float type '%s' is expected to be in the form of 'f[N]' where N is 16, 32 or 64 "
                  "but found '%s' instead.",
                  n.c_str(),
                  bitsString.c_str())
      );
    }
    return ctx->getPrimitiveNumberType<types::FloatType>(bits);
  }

  STYPE_INSTANCE(REMOVE_REFERENCES_STYPE) {
    ASSERT_GENERICS(1, REMOVE_REFERENCES_STYPE)
    auto generic = generics.at(0);
    auto type = transformType(generic);
    if (auto ref = utils::cast<types::ReferenceType>(type)) { return ref->getPointedType(); }
    return type;
  }

  STYPE_INSTANCE(FUNCTION_RETURN_STYPE) {
    ASSERT_GENERICS(1, FUNCTION_RETURN_STYPE)
    auto generic = generics.at(0);
    auto type = transformType(generic);
    auto fnType = getFunctionType(type);
    if (fnType) { return fnType->getRetType(); }
    E<TYPE_ERROR>(
            ty,
            FMT("Type '%i' expected first generic parameter to "
                "be a function but it found type '%s'.",
                FUNCTION_RETURN_STYPE.c_str(),
                type->getPrettyName().c_str())
    );
  }

  return nullptr;
}

} // namespace Syntax
} // namespace snowball
