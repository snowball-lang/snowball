
#include "../common.h"
#include "ImportCache.h"

#ifndef __SNOWBALL_SERVICES_IMPORT_H_
#define __SNOWBALL_SERVICES_IMPORT_H_

namespace snowball {
namespace services {

/**
 * @brief It manages imports and module caches
 */
class ImportService {
 public:
  /// @brief A cache containing all of the alread-generated modules
  ///  used at compile time.
  ImportCache* cache = new ImportCache();
  /// @brief A list of possible pre-defined file extensions used to
  /// search
  ///  if no extension has been defined.
  const std::vector<std::string> extensions = {".sn", /* TODO */};
  /// @brief Core library custom UUID
  static const std::string CORE_UUID;
  /// @brief Path to the current package being generated
  std::filesystem::path currentPackagePath;
  /// @brief Root path to the packages folder
  std::filesystem::path packagesPath;

 public:
  ImportService(std::filesystem::path packagesPath) : packagesPath(packagesPath) {}
  /**
   * @brief Get the package path based on it's identifier
   * @note if package name is "pkg" it will return the current package
   *  being generated
   */
  std::filesystem::path getPackagePath(const std::string package);
  /**
   * @brief Get the corresponding import path from a set of rules.
   * @note The path will be absolute and paths will be returned if the
   * file exist.
   *
   * @param package package to search from (e.g. std). @note if the
   * package is
   * "pkg" it will find inside the current package being generated.
   * @param path the path to search for
   * @param extension extension to find for (search for common ones
   * for )
   * @return std::filesystem::path found path to import and
   * std::string an error message if any
   */
  std::tuple</*result path*/std::filesystem::path, /*original path*/std::filesystem::path, /*errors*/std::string>
      getImportPath(const std::string package, std::vector<std::string> path, const std::string extension = "");
  /**
   * @brief Check if a module is external or not
   */
  bool isExternalModule(std::string package);
  /**
   * @brief Gets the exported name based on the path if the export
   * symbol is empty.
   */
  std::string getExportName(std::filesystem::path path, std::string symbol);
  /**
   * @brief Get the respective UUID based on the path it's imported
   * from
   *
   * @param path path to transform
   * @return std::string resultant UUID for the module path.
   */
  std::string getModuleUUID(std::filesystem::path path);
  /**
   * @brief Get the current package path
   */
  std::filesystem::path getCurrentPackagePath() const { return currentPackagePath; }
  /**
   * @brief Set the current package path
   */
  void setCurrentPackagePath(std::filesystem::path path) { currentPackagePath = path; }
  /**
   * @brief Get the packages path
   */
  std::filesystem::path getPackagesPath() const { return packagesPath; }
};

} // namespace services
} // namespace snowball

#endif // __SNOWBALL_SERVICES_IMPORT_H_
