
#include "Type.h"
#include "PointerType.h"

#include "../syntax/nodes.h"

namespace snowball {
namespace types {

Syntax::Expression::TypeRef *Type::toRef() {
    auto ty = Syntax::TR(getName(), nullptr);
    return ty;
}

std::shared_ptr<Type> Type::getPointerTo() {
    return std::make_shared<PointerType>(shared_from_this());
}

} // namespace types
} // namespace snowball
