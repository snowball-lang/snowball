
#include "ImportService.h"

#include "../utils/utils.h"
#include "../vendor/toml.hpp"

#include <unistd.h>

namespace fs = std::filesystem;

namespace snowball {
namespace services {

inline const std::string ImportService::CORE_UUID = "@sn.std.";
fs::path ImportService::getPackagePath(const std::string package) {
  if (package == "std") {
    return (fs::path) utils::get_lib_folder();
  } else if (package == "pkg") {
    return fs::current_path();
  }

  return getPackagesPath() / (_SNOWBALL_PACKAGES_DIR) / package;
}

std::string ImportService::getExportName(std::filesystem::path path, std::string symbol) {
  return symbol.empty() ? path.stem().string() : symbol;
}

bool ImportService::isExternalModule(std::string package) { return package != "pkg"; }

std::string ImportService::getModuleUUID(std::filesystem::path path) {
  std::string result = path.string();
  utils::replaceAll(result, PATH_SEPARATOR, "::");

  return "pkg" + result;
}

std::pair<fs::path, std::string>
ImportService::getImportPath(const std::string package, std::vector<std::string> path, const std::string extension) {
  auto packagePath = getPackagePath(package);

  fs::path definedPath;
  for (auto p : path) { definedPath /= p; }

  fs::path fullPath = packagePath / definedPath;
  bool exists = false;
  std::string foundExt;

  // if it's a directory
  if (fs::is_directory(fullPath)) {
    auto configFile = fullPath / "sn.toml";
    auto config = toml::parse_file(configFile.string());
    auto entry = config["package"]["main"].value_or<std::string>("<invalid>");
    if (entry == "<invalid>") {
      return {"", "Package doesn't have a main entry defined!"};
    }

    assert(access((fullPath / entry).c_str(), F_OK) != -1);
    return {fullPath / entry, ""};
  } else {
    for (auto ext : extensions) {
      if (exists) { return {"", "Multiple paths found without an extension defined"}; }

      exists = access((fullPath.string() + ext).c_str(), F_OK) != -1;
      if (exists) { foundExt = ext; }
    }
  }

  if (!exists) {
    return {"",
            FMT("Coudnt find module '%s' imported from '%s' (%s)!",
                utils::join(path.begin(), path.end(), "::").c_str(),
                package.c_str(), fullPath.string().c_str())};
  }

  return {fullPath.string() + foundExt, ""};
}

} // namespace services
} // namespace snowball
