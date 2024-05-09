

#ifndef __SNOWBALL_PACKAGE_CONFIG_H__
#define __SNOWBALL_PACKAGE_CONFIG_H__

#include <optional>
#include <vector>

namespace snowball {

struct PackageConfigBase {
  struct Project {
    std::string name;
    std::string version;
    std::string description;
    std::string main;
    std::string type = "both"; // "lib", "exe", "both"
    std::vector<std::string> authors;
    std::string license;
    std::filesystem::path path;
  } project;

  struct Build {
    std::vector<std::string> linkage_libs;
  } build;
};

using PackageConfig = std::optional<PackageConfigBase>;

}

#endif // __SNOWBALL_PACKAGE_CONFIG_H__

