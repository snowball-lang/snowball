
#include "../Transformer.h"

#include <algorithm>
#include <llvm/IR/Attributes.h>

#define STYPE_INSTANCE(x) if (n == x)
#define ASSERT_GENERICS(n, t)                                                                      \
    auto generics = ty->getGenerics();                                                             \
    if (generics.size() != n) {                                                                    \
        E<TYPE_ERROR>(ty->getDBGInfo(),                                                            \
                      FMT("Expected '%i' generics for '%s' but got '%i' instead",                  \
                          n,                                                                       \
                          t.c_str(),                                                               \
                          generics.size()));                                                       \
    }

namespace snowball {
namespace Syntax {

inline const std::string FUNCTION_RETURN_STYPE = "Core::ReturnType";
inline const std::string SIZED_TYPE_CHECK_STYPE = "Core::Sized";

std::shared_ptr<types::Type>
Transformer::transformSpecialType(Expression::TypeRef* ty) {
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
        auto isVoid = utils::dyn_cast<types::VoidType>(type);

        // TODO: check for other instances
        if (utils::dyn_cast<types::VoidType>(type)) { 
            E<TYPE_ERROR>(ty,
                FMT("Type '%s' is expected to contain a known size at compile time but found '%s'.",
                    SIZED_TYPE_CHECK_STYPE.c_str(),
                    type->getPrettyName().c_str()), ErrorInfo {
                    // TODO: instead of showing the call, show somthing like:
                    //  typeGenerationBacktrace.at(1)
                    //.tail = ctx->createErrorTail(ctx->latestCall)
                });
        }

        return type;
    }

    return nullptr;
}

} // namespace Syntax
} // namespace snowball
