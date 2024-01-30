
#include "ReferenceType.h"

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

ReferenceType::ReferenceType(Type* base) : AcceptorExtend(Kind::TYPE, "&" + base->getName()), base(base) {
}
Type* ReferenceType::getPointedType() const { return base; }
std::string ReferenceType::getPrettyName() const {
  auto baseName = base->getPrettyName();
  return "&" + baseName;
}

std::string ReferenceType::getMangledName() const {
  auto mangledBase = base->getMangledName();
  return mangledBase + ".r";
}

Syntax::Expression::TypeRef* ReferenceType::toRef() {
  auto tRef = new Syntax::Expression::ReferenceType(base->toRef(), getDBGInfo());
  return tRef;
}

Type* ReferenceType::getBaseType() const {
  if (auto c = utils::cast<ReferenceType>(base)) return c->getBaseType();
  return base;
}

bool ReferenceType::canCast(Type* ty) const {
  SNOWBALL_MUTABLE_CAST_CHECK
  if (auto c = utils::cast<ReferenceType>(ty)) return base->canCast(c->getPointedType());
  return false;
}

void ReferenceType::setMutable(bool m) {
  _mutable = m;
}

}; // namespace types
}; // namespace snowball
