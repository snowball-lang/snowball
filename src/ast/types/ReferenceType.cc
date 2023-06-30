
#include "ReferenceType.h"
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

ReferenceType::ReferenceType(std::shared_ptr<Type> base)
    : AcceptorExtend(Kind::TYPE, base->getName() + "&"), base(base) { }
std::shared_ptr<Type> ReferenceType::getReferencedType() const { return base; }
std::string ReferenceType::getPrettyName() const {
    auto baseName = base->getPrettyName();
    return baseName + "&";
}

std::string ReferenceType::getMangledName() const {
    auto mangledBase = base->getMangledName();
    return mangledBase + ".r";
}

Syntax::Expression::TypeRef* ReferenceType::toRef() {
    auto tRef = Syntax::TR("$referenceType:" + std::to_string(getId()), nullptr, shared_from_this());
    return tRef;
}

std::shared_ptr<Type> ReferenceType::getBaseType() const {
    if (auto c = utils::dyn_cast<ReferenceType>(base)) { return c->getBaseType(); }
    if (auto c = utils::dyn_cast<PointerType>(base)) { return c->getBaseType(); }

    return base;
}

bool ReferenceType::canCast(Type* ty) const {
    if (auto c = utils::cast<ReferenceType>(ty)) { return base->canCast(c->getReferencedType()); }

    return false;
}

}; // namespace types
}; // namespace snowball
