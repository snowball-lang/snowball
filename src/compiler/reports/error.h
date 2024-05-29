
#ifndef __SNOWBALL_COMPILER_REPORTS_ERROR_H__
#define __SNOWBALL_COMPILER_REPORTS_ERROR_H__

#include "compiler/frontend/location.h"
#include <optional>
#include <string>

namespace snowball {

class Error : public frontend::LocationHolder {
public:
  struct Info {
    std::string highlight = "";
    std::string help = "";
    std::string note = "";
    std::string see = "";
    std::vector<std::pair<frontend::SourceLocation, Info>> related = {};
  };
  enum class Type
  {
    Err,
    Warn,
    Fatal
  };

private:
  std::string message;
  Info info;
  Type type = Type::Err;

public:
  Error(const std::string& message, const frontend::SourceLocation& location)
    : frontend::LocationHolder(location)
    , message(message) {}
  Error(const std::string& message, const frontend::SourceLocation& location,
        const Info& info)
    : frontend::LocationHolder(location)
    , message(message)
    , info(info) {}
  Error(const std::string& message, const frontend::SourceLocation& location,
        const Info& info, const Type& type)
    : frontend::LocationHolder(location)
    , message(message)
    , info(info)
    , type(type) {}
  Error(const std::string& message, const frontend::SourceLocation& location,
        const Type& type)
    : frontend::LocationHolder(location)
    , message(message)
    , type(type) {}

  std::string get_message() const { return message; }
  Info get_info() const { return info; }
  Type get_type() const { return type; }

  void print(bool = false);
};

template <typename... Args>
auto E(Args&&... args) {
  return Error(std::forward<Args>(args)...);
}

} // namespace snowball

#endif // __SNOWBALL_COMPILER_REPORTS_ERROR_H__
