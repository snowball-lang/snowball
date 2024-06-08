
#ifndef __SNOWBALL_GLOBALS_H__
#define __SNOWBALL_GLOBALS_H__

#include <cassert>
#include <filesystem>
#include <fstream>
#include <functional>

#include "utils/utils.h"
#include "compiler/ctx.h"

namespace snowball {
namespace globals {
static std::function<std::string(const std::filesystem::path&)> read_file =
        [](const std::filesystem::path& path) -> std::string {
  std::ifstream ostr(path);
  sn_assert(
          ostr.is_open(), "File not found at path: " + path.string()
  ); // we make sure the file exists before calling this function

  std::ostringstream sstr;
  sstr << ostr.rdbuf();
  return sstr.str();
};
}


struct GlobalContext {
  bool verbose = false;
  bool debug_verbose = false;

  utils::TimerType timer_type = utils::TimerType::None;

  // Build options
  EmitType emit_type = EmitType::Executable;
  OptLevel opt_level = OptLevel::Debug;

  // Output options
  Target target = Target::Unknown;
  Arch arch = Arch::Unknown;
  bool static_link = false;
};

extern GlobalContext* global;

} // namespace snowball

#endif // __SNOWBALL_GLOBALS_H__
