
#ifndef __SNOWBALL_GLOBALS_H__
#define __SNOWBALL_GLOBALS_H__

#include <filesystem>
#include <functional>
#include <fstream>

#include "utils/utils.h"

namespace snowball {
namespace globals {
static std::function<std::string(const std::filesystem::path&)> read_file = [](const std::filesystem::path& path) -> std::string {
  std::ifstream ostr(path);
  sn_assert(ostr.is_open(), "File not found."); // we make sure the file exists before calling this function

  std::ostringstream sstr;
  sstr << ostr.rdbuf();
  return sstr.str();
};
}
}

#endif // __SNOWBALL_GLOBALS_H__
