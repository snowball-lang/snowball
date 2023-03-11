#include "PrimitiveTypes.h"

#include "../../utils/utils.h"

using namespace snowball::utils;
namespace snowball::types {
bool NumericType::isNumericType(ptr<Type> ty) {
    return (cast<NumericType>(ty) != nullptr);
}
} // namespace snowball::types
