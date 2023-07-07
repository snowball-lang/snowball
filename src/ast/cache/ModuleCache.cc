
#include "ModuleCache.h"

namespace snowball {
namespace Syntax {
namespace cacheComponents {

void Modules::addModule(const std::string& uuid, std::shared_ptr<ir::Module> module) {
    assert(!getModule(uuid).has_value());
    modules[uuid] = module;
}

std::optional<std::shared_ptr<ir::Module>> Modules::getModule(const std::string& uuid) {
    auto f = modules.find(uuid);
    if (f != modules.end()) return f->second;

    return std::nullopt;
}

} // namespace cacheComponents
} // namespace Syntax
} // namespace snowball
