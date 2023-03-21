
#include "../../DBGSourceInfo.h"
#include "../../common.h"
#include "Module.h"

/**
 * @brief Snowball module
 *
 * Snowball modules are used as containers
 * that are represented as programs for our
 * generator to use.
 *
 * Modules may contain things such as type
 * declarations, enviroments and functions.
 */
namespace snowball {
namespace ir {

Module::Module(const std::string name, const std::string uuid,
               std::shared_ptr<Module> parent)
    : name(name), uniqueName(uuid.empty() ? name : uuid), parent() {}

std::string Module::getName() const {
    return (parent == nullptr ? "" : parent->getName() + "::") + name;
}
std::string Module::getUniqueName() const { return uniqueName; }

} // namespace ir
} // namespace snowball