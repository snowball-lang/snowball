
#include "ImportCache.h"

#include "../utils/utils.h"

#include <optional>
#include <unistd.h>

// clang-format off
namespace fs = std::filesystem;

namespace snowball {
namespace services {

void ImportCache::addModule(fs::path p, std::shared_ptr<ir::Module> m)
    { auto i = modules.find(p); assert(i == modules.end());
    modules.insert({p, m}); }
std::optional<std::shared_ptr<ir::Module>>
ImportCache::getModule(fs::path p) {
    auto i = modules.find(p);
    return i == modules.end() ? std::nullopt :
        std::make_optional<std::shared_ptr<ir::Module>>(i->second);
}

// clang-format on

} // namespace services
} // namespace snowball
