
#include "Type.h"

#include "../syntax/nodes.h"
#include "ReferenceType.h"

namespace snowball {
namespace types {

Type::Type(Kind p_kind, std::string p_name, bool isMutable) : kind(p_kind), name(p_name), _mutable(isMutable) { }
Type::Type(Kind p_kind, bool isMutable) : kind(p_kind), _mutable(isMutable) { }

Syntax::Expression::TypeRef* Type::toRef() {
    auto ty = Syntax::TR(getName(), NO_DBGINFO, nullptr, getName());
    return ty;
}

std::shared_ptr<Type> Type::copy() const 
    { assert(!"called copy to not-specialised type!"); }
std::shared_ptr<Type> Type::getPointerTo() 
    { return std::make_shared<ReferenceType>(shared_from_this()); }

} // namespace types
} // namespace snowball
