
#include "../ir/module/Module.h"

#include <filesystem>
#include <optional>
#include <unordered_map>

#ifndef __SNOWBALL_IMPORT_CACHE_H_
#define __SNOWBALL_IMPORT_CACHE_H_

namespace snowball {
namespace services {

/**
 * @brief It keeps track of the already-imported modules
 *  and stores them as a cache.
 */
class ImportCache {
    /// @brief A map containing the stored modules.
    /// @note The map key is a full abstract path.
    std::unordered_map<std::filesystem::path, std::shared_ptr<ir::Module>>
        modules;

  public:
    ImportCache();

    /// @brief Set a new module to the map
    void addModule(std::filesystem::path p, std::shared_ptr<ir::Module> m);
    /// @return a shared pointer to a module if it exists inside the map
    std::optional<std::shared_ptr<ir::Module>>
    getModule(std::filesystem::path p, std::shared_ptr<ir::Module> m);

    ~ImportCache() noexcept = default;
};

} // namespace services
} // namespace snowball

#endif // __SNOWBALL_IMPORT_CACHE_H_
