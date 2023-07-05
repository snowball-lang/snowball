
#include "Type.h"

#include "../syntax/nodes.h"
#include "PointerType.h"

namespace snowball {
namespace types {

Type::Type(Kind p_kind, std::string p_name, bool isMutable)
    : kind(p_kind), name(p_name), _mutable(isMutable) { }
Type::Type(Kind p_kind, bool isMutable) : kind(p_kind), _mutable(isMutable) { }

Syntax::Expression::TypeRef* Type::toRef() {
    auto ty = Syntax::TR(getName(), nullptr);
    return ty;
}

std::shared_ptr<Type> Type::getPointerTo() {
    return std::make_shared<PointerType>(shared_from_this());
}

} // namespace types
} // namespace snowball
