#include "PrimitiveTypes.h"

#include "../../utils/utils.h"

namespace snowball::types {
bool NumericType::isNumericType(Type* ty) { return utils::is<NumericType>(ty); }
} // namespace snowball::types
