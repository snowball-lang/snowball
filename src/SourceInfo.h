
#include <string>
#include <filesystem>

#ifndef __SNOWBALL_SOURCE_INFO_H_
#define __SNOWBALL_SOURCE_INFO_H_

namespace snowball {

/**
 * @brief The source info is used so that the compiler knows
 *  where and what it's currently compiling
 */
class SourceInfo {
 public:
  SourceInfo(std::string p_code = "", std::string p_path = "<anonimus>")
      : source(p_code), path(((std::filesystem::path)p_path).lexically_normal()), source_length(p_code.size()){};

  /// @brief Get the source content for the file
  std::string getSource() const { return source; };
  /// @return The current file being working on
  std::string getPath() const { return path; };

  const int source_length = 0;
  ~SourceInfo() noexcept = default;

 private:
  std::string source;
  std::string path;
};
} // namespace snowball

#endif // __SNOWBALL_SOURCE_INFO_H_
