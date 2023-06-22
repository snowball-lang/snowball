
#include <string>

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
        : _code(p_code), _path(p_path), source_length(p_code.size()){};

    /// @brief Get the source content for the file
    std::string
    getSource() const {
        return _code;
    };
    /// @return The current file being working on
    std::string
    getPath() const {
        return _path;
    };

    const int source_length = 0;
    ~SourceInfo() noexcept = default;

  private:
    std::string _code;
    std::string _path;
};
} // namespace snowball

#endif // __SNOWBALL_SOURCE_INFO_H_
