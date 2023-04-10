
#include "Type.h"

#include "../syntax/nodes.h"

namespace snowball {
namespace types {

Syntax::Expression::TypeRef* Type::toRef() {
    auto ty = Syntax::TR(getName(), nullptr);
    return ty;
}

} // namespace types
} // namespace snowball
