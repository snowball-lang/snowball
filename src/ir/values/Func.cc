
#include "Func.h"

#include "../../services/OperatorService.h"
#include "../../utils/utils.h"
#include "Argument.h"

#include <string>

namespace snowball {
namespace ir {

Func::Func(std::string identifier, bool declaration, bool variadic,
           std::shared_ptr<types::DefinedType> parent)
    : declaration(declaration), variadic(variadic), identifier(identifier),
      parent(parent) {}

Func::Func(std::string identifier, Func::FunctionArgs arguments,
           bool declaration, bool variadic,
           std::shared_ptr<types::DefinedType> parent)
    : declaration(declaration), variadic(variadic), identifier(identifier),
      parent(parent) {

    setArgs(arguments);
}

Func::Func(std::string identifier, std::shared_ptr<Block> body,
           bool declaration, bool variadic,
           std::shared_ptr<types::DefinedType> parent)
    : declaration(declaration), variadic(variadic), identifier(identifier),
      parent(parent) {

    setBody(body);
}

Func::Func(std::string identifier, std::shared_ptr<Block> body,
           Func::FunctionArgs arguments, bool declaration, bool variadic,
           std::shared_ptr<types::DefinedType> parent)
    : declaration(declaration), variadic(variadic), identifier(identifier),
      parent(parent) {

    setBody(body);
    setArgs(arguments);
}

bool Func::isConstructor() {
    return (services::OperatorService::getOperatorMangle(
                services::OperatorService::CONSTRUCTOR) == identifier) &&
           hasParent();
}

std::string Func::getIdentifier() { return identifier; }
std::string Func::getName(bool ignoreOperators) {
    if (services::OperatorService::isOperator(identifier) && (!ignoreOperators)) {
        auto op = services::OperatorService::operatorID(identifier);
        return services::OperatorService::operatorName(op);
    }

    return identifier;
}

Func::FunctionArgs Func::getArgs(bool ignoreSelf) const {
    auto argv = arguments;
    if (ignoreSelf && argv.size() > 0 && (hasParent() && (!_static)) &&
        hasParent()) {
        argv.erase(argv.begin());
    }

    return argv;
}

bool Func::isExternal(std::string name) {
    return !utils::startsWith(name, _SN_MANGLE_PREFIX);
}

std::string Func::getNiceName() {
    auto moduleBase = module->isMain() ? "" : module->getName() + "::";
    auto base       = hasParent() ? (parent->getPrettyName() + "::") : "";
    auto n          = moduleBase + base + getName();

    return n;
}

std::string Func::getMangle() {

    if (!externalName.empty()) return externalName;

    // TODO: add class to here
    auto base =
        hasParent() ? parent->getMangledName() : module->getUniqueName();
    auto name = identifier;

    std::string prefix = (utils::startsWith(base, _SN_MANGLE_PREFIX)
                              ? base
                              : (_SN_MANGLE_PREFIX + base)) +
                         +"&" + std::to_string(name.size()) +
                         name // Function name with modules
                         + "Cv" + std::to_string(getId()); // disambiguator

    std::string mangledArgs = "Sa";                        // Start args tag

    int argCounter = 1;
    for (auto a : arguments) {
        mangledArgs += "A" + std::to_string(argCounter) +
                       a.second->getType()->getMangledName();
        argCounter++;
    }

    std::string mangled = prefix + mangledArgs + "FnE"; // FnE = end of function
    return mangled;
}

} // namespace ir
} // namespace snowball
