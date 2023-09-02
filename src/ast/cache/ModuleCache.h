
#include <assert.h>
#include <optional>
#include <string>
#include <vector>

#include "../../ir/module/Module.h"

#ifndef __SNOWBALL_AST_MODULE_CACHE_H_
#define __SNOWBALL_AST_MODULE_CACHE_H_

namespace snowball {
namespace Syntax {

namespace cacheComponents {

/**
 * @brief Cache component for modules. This is used
 *  for caching modules that are imported.
 */
class Modules {
 protected:
  /// @brief A global map containing each module.
  std::map<std::string, std::shared_ptr<ir::Module>> modules;

 public:
  /// @brief add a new module to the cache
  void addModule(const std::string& uuid, std::shared_ptr<ir::Module> module);
  /// @brief get a module from the cache
  std::optional<std::shared_ptr<ir::Module>> getModule(const std::string& uuid);
};

} // namespace cacheComponents
} // namespace Syntax
} // namespace snowball

#endif // __SNOWBALL_AST_MODULE_CACHE_H_
