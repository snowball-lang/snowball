
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

namespace snowball
{
namespace Syntax
{

inline const std::string FUNCTION_RETURN_STYPE = "Core::ReturnType";

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

    return nullptr;
}

} // namespace Syntax
} // namespace snowball
