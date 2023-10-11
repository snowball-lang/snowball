
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

PointerType::PointerType(Type* base, bool isMutable) : AcceptorExtend(Kind::TYPE, base->getName()), base(base) {
  setMutable(isMutable);
}
Type* PointerType::getPointedType() const { return base; }
std::string PointerType::getPrettyName() const {
  auto baseName = base->getPrettyName();
  return "*" + (std::string)(isMutable() ? "mut " : "const ") + baseName;
}

std::string PointerType::getMangledName() const {
  auto mangledBase = base->getMangledName();
  return mangledBase + ".p";
}

Syntax::Expression::TypeRef* PointerType::toRef() {
  auto tRef = new Syntax::Expression::PointerType(base->toRef(), isMutable(), getDBGInfo());
  return tRef;
}

Type* PointerType::getBaseType() const {
  if (auto c = utils::cast<PointerType>(base)) return c->getBaseType();
  return base;
}

bool PointerType::canCast(Type* ty) const {
  SNOWBALL_MUTABLE_CAST_CHECK

  if (auto c = utils::cast<PointerType>(ty)) return base->canCast(c->getPointedType());
  return false;
}

void PointerType::setMutable(bool m) {
  _mutable = m;
  name = m ? _SNOWBALL_MUT_PTR : _SNOWBALL_CONST_PTR;
}

}; // namespace types
}; // namespace snowball
