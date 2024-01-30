

#include <filesystem>
#include <string>
#include <vector>
#include <unistd.h>

#include "vendor/toml.hpp"

#include "../utils/utils.h"
#include "../errors.h"
#include "../constants.h"
#include "../os/Driver.h"

#include "nlohmann/json.hpp"

#ifndef __SNOOZE__APP__PM__MANAGER_H__
#define __SNOOZE__APP__PM__MANAGER_H__

namespace snowball {
namespace pm {

struct Package {
  std::string name;
  std::string version;

  std::vector<Package> dependencies;
};

/**
 * @brief Snowball's package manager.
 *
 * This class is responsible for managing packages on the system.
 * It is responsible for installing, removing, and updating packages.
 *  - Installing packages
 *  - Removing packages
 *  - Updating packages
 *  - Listing packages
 *  - Searching for packages
 *  - Querying packages
 *  ...
 *
 * Packages are installed from a git repository. The git repository
 * contains a package manifest file, which is a toml file that
 * describes the package.
*/
class Manager {
  toml::parse_result package;
  bool silent;
  std::string cwd;
  std::string configFolder;

 public:
  Manager(toml::parse_result p_package, bool p_silent, std::string p_cwd, std::string p_configFolder);

  int runAsMain();
  std::string getGit();

  bool isInstalled(Package p_package);
  int install(Package p_package);

  nlohmann::json getPackageInfoFromRepo(std::string package);
};

} // namespace pm
} // namespace snowball

#endif // __SNOOZE__APP__PM__MANAGER_H__
