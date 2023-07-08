
#include "PointerType.h"

#include "../../common.h"
#include "../../constants.h"
#include "../../ir/values/Func.h"
#include "../../utils/utils.h"
#include "../syntax/common.h"
#include "Type.h"

#include <memory>
#include <sstream>
#include <string>
#include <vector>

namespace snowball {
namespace types {

PointerType::PointerType(std::shared_ptr<Type> base)
    : AcceptorExtend(Kind::TYPE, base->getName() + "*"), base(base) { }
std::shared_ptr<Type> PointerType::getPointedType() const { return base; }
std::string PointerType::getPrettyName() const {
    auto baseName = base->getPrettyName();
    return baseName + "*";
}

std::string PointerType::getMangledName() const {
    auto mangledBase = base->getMangledName();
    return mangledBase + ".p";
}

Syntax::Expression::TypeRef* PointerType::toRef() {
    auto tRef = Syntax::TR("$pointerType:" + std::to_string(getId()), nullptr, shared_from_this());
    return tRef;
}

std::shared_ptr<Type> PointerType::getBaseType() const {
    if (auto c = utils::dyn_cast<PointerType>(base)) { return c->getBaseType(); }

    return base;
}

bool PointerType::canCast(Type* ty) const {
    SNOWBALL_COBJ_CAST_CHECK
    SNOWBALL_MUTABLE_CAST_CHECK

    if (auto c = utils::cast<PointerType>(ty)) return base->canCast(c->getPointedType());
    return false;
}

}; // namespace types
}; // namespace snowball
