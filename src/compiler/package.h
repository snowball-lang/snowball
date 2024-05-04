

#ifndef __SNOWBALL_CTX_H__
#define __SNOWBALL_CTX_H__

#include <optional>

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
  } project;

  struct Build {
    std::vector<std::string> linkage_libs;
  } build;
}

using PackageConfig = std::optional<PackageConfigBase>;

}

#endif // __SNOWBALL_CTX_H__

