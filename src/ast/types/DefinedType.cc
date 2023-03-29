
#include "DefinedType.h"

#include "../../common.h"
#include "../../constants.h"
#include "../../ir/values/Func.h"
#include "../../utils/utils.h"
#include "../syntax/common.h"
#include "Type.h"

#include <memory>
#include <string>
#include <vector>

namespace snowball {
namespace types {

DefinedType::DefinedType(const std::string& name, const std::string uuid,
                         std::shared_ptr<ir::Module> module,
                         std::vector<ptr<ClassField>> fields,
                         std::shared_ptr<DefinedType> parent,
                         std::vector<std::shared_ptr<Type>> generics)
    : AcceptorExtend(Kind::CLASS, name), uuid(uuid), parent(parent),
      module(module), fields(fields), generics(generics) {}

DefinedType::ClassField::ClassField(const std::string& name,
                                    std::shared_ptr<Type> type, Privacy privacy)
    : name(name), type(type), Syntax::Statement::Privacy(privacy) {}
std::string DefinedType::getUUID() const { return uuid; }
std::shared_ptr<ir::Module> DefinedType::getModule() const { return module; }
int DefinedType::getVtableSize() { return vtableSize; }
int DefinedType::addVtableItem() { return vtableSize++; }

bool DefinedType::is(ptr<DefinedType> other) {
    auto otherArgs = other->getGenerics();
    bool argumentsEqual =
        std::all_of(otherArgs.begin(), otherArgs.end(),
                    [&, idx = 0](std::shared_ptr<Type> i) mutable {
                        return generics.at(idx)->is(i);
                        idx++;
                    });
    return (other->getUUID() == uuid) && argumentsEqual;
}

std::string DefinedType::getPrettyName() const {
    auto base = module->isMain() ? "" : module->getName() + "::";
    auto n    = base + getName();

    std::string genericString; // Start args tag
    if (generics.size() > 0) {
        genericString = "<";

        for (auto g : generics) {
            genericString += g->getPrettyName();
        }

        genericString += ">";
    }

    return n + genericString;
}

std::string DefinedType::getMangledName() const {
    auto base = module->getUniqueName();

    std::string prefix =
        (utils::startsWith(base, _SN_MANGLE_PREFIX) ? base
                                                    : _SN_MANGLE_PREFIX) +
        "&" + std::to_string(name.size()) + name // Class name with modules
        + "Cv" + std::to_string(getId());        // disambiguator

    std::string mangledArgs;                     // Start args tag
    if (generics.size() > 0) {
        mangledArgs = "ClsGSt";

        int argCounter = 1;
        for (auto g : generics) {
            mangledArgs +=
                "A" + std::to_string(argCounter) + g->getMangledName();
            argCounter++;
        }
    }

    std::string mangled = prefix + mangledArgs + "ClsE"; // ClsE = end of class
    return mangled;
}

ptr<Syntax::Expression::TypeRef> DefinedType::toRef() {
    auto tRef = Type::toRef();
    std::vector<ptr<Syntax::Expression::TypeRef>> genericRef;
    for (auto g : generics) {
        genericRef.push_back(g->toRef());
    }

    tRef->setGenerics(genericRef);
    return tRef;
}

}; // namespace types
}; // namespace snowball
