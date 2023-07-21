
#include "TypeAlias.h"

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

TypeAlias::TypeAlias(const std::string name, Type* base)
    : AcceptorExtend(Kind::TYPE, name), base(base) { }
std::string TypeAlias::getPrettyName() const {
    auto baseName = base->getPrettyName();
    auto base = module->isMain() ? "" : module->getName() + "::";
    auto n = base + getName();

    std::string genericString; // Start args tag
    if (generics.size() > 0) {
        genericString = "<";

        for (auto g : generics) { genericString += g->getPrettyName(); }

        genericString += ">";
    }

    return n + genericString + " { aka " + baseName + " }";
}

std::string TypeAlias::getMangledName() const { return base->getMangledName(); }

Syntax::Expression::TypeRef* TypeAlias::toRef() {
    auto tRef = Syntax::TR(getName(), nullptr, this, getUUID());
    return tRef;
}

Type* TypeAlias::getBaseType() const { return base; }

bool TypeAlias::canCast(Type* ty) const { return base->canCast(ty); }

}; // namespace types
}; // namespace snowball
