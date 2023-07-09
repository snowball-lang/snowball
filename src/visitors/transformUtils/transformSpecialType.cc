
#include "../Transformer.h"

#include <algorithm>
#include <llvm/IR/Attributes.h>

#define STYPE_INSTANCE(x) if (n == x)
#define ASSERT_GENERICS(n, t)                                                                      \
    auto generics = ty->getGenerics();                                                             \
    if (generics.size() != n) {                                                                    \
        E<TYPE_ERROR>(ty->getDBGInfo(),                                                            \
                      FMT("Expected '%i' generics for '%s' but got '%i' instead", n, t.c_str(),    \
                          generics.size()));                                                       \
    }

namespace snowball {
namespace Syntax {

inline const std::string FUNCTION_RETURN_STYPE = "Core::ReturnType";
inline const std::string SIZED_TYPE_CHECK_STYPE = "Core::Sized";
inline const std::string IS_NUMERIC_CHECK_STYPE = "Core::IsNumeric";
inline const std::string IS_POINTER_CHECK_STYPE = "Core::IsPointer";
inline const std::string CASTABLE_TO_CHECK_STYPE = "Core::CastableTo";
inline const std::string IMPLEMENTS_CHECK_STYPE = "Core::Implements";

std::shared_ptr<types::Type> Transformer::transformSpecialType(Expression::TypeRef* ty) {
    auto n = ty->getName();

    STYPE_INSTANCE(FUNCTION_RETURN_STYPE) {
        ASSERT_GENERICS(1, FUNCTION_RETURN_STYPE)

        auto generic = generics.at(0);
        auto type = transformType(generic);
        auto fnType = utils::dyn_cast<types::FunctionType>(type);
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
        if (utils::dyn_cast<types::VoidType>(type)) {
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
        if (auto x = utils::dyn_cast<types::PrimitiveType>(type);
            !((x == nullptr) || types::NumericType::isNumericType(x.get()))) {
            E<TYPE_ERROR>(ty,
                          FMT("Type '%s' is expected to be a numeric type but found '%s'!",
                              IS_NUMERIC_CHECK_STYPE.c_str(),
                              type->getPrettyName().c_str()));
        }

        return type;
    }

    STYPE_INSTANCE(IS_POINTER_CHECK_STYPE) {
        ASSERT_GENERICS(1, IS_POINTER_CHECK_STYPE)

        auto generic = generics.at(0);
        auto type = transformType(generic);

        // TODO: check for other instances
        if (!utils::dyn_cast<types::ReferenceType>(type)) {
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
            E<TYPE_ERROR>(
                    ty,
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

        auto definedType = utils::dyn_cast<types::DefinedType>(childType);
        if (!definedType || !definedType->hasParent() ||
            !definedType->getParent()->is(parentType.get())) {
            E<TYPE_ERROR>(ty,
                          FMT("Type '%s' expected type '%s' to be a subtype of '%s' but it isn't!",
                              IMPLEMENTS_CHECK_STYPE.c_str(), childType->getPrettyName().c_str(),
                              parentType->getPrettyName().c_str()));
        }

        return childType;
    }

    return nullptr;
}

} // namespace Syntax
} // namespace snowball
