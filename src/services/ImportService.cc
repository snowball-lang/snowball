
#include "ImportService.h"

#include "../utils/utils.h"

#include <unistd.h>

namespace fs = std::filesystem;

namespace snowball {
namespace services {

inline const std::string ImportService::CORE_UUID = "@sn::Core::";
fs::path ImportService::getPackagePath(const std::string package) {
    if (package == "Core") {
        return utils::get_lib_folder();
    } else if (package == "$") {
        return fs::current_path();
    }

    return ((fs::path)_SNOWBALL_PACKAGES_DIR) / package;
}

std::string ImportService::getExportName(std::filesystem::path path,
                                         std::string symbol) {
    return symbol.empty() ? path.stem().string() : symbol;
}

std::string ImportService::getModuleUUID(std::filesystem::path path) {
    std::string result = path.string();
    utils::replaceAll(result, PATH_SEPARATOR, "::");

    return "$" + result;
}

std::pair<fs::path, std::string>
ImportService::getImportPath(const std::string package,
                             std::vector<std::string> path,
                             const std::string extension) {
    auto packagePath = getPackagePath(package);
    bool isPackage   = package == "$";

    fs::path definedPath;
    for (auto p : path) {
        definedPath /= p;
    }

    fs::path fullPath = packagePath / definedPath;
    bool exists       = false;
    std::string foundExt;

    for (auto ext : extensions) {
        if (exists) {
            return {"", "Multiple paths found without an extension defined"};
        }

        exists = access((fullPath.string() + ext).c_str(), F_OK) != -1;
        if (exists) {
            foundExt = ext;
        }
    }

    if (!exists) {
        return {"", FMT("Coudn't find module imported from '%s'!",
                        package.c_str())};
    }

    return {fullPath.string() + foundExt, ""};
}

} // namespace services
} // namespace snowball
