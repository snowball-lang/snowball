
#ifndef __SNOWBALL_GLOBALS_H__
#define __SNOWBALL_GLOBALS_H__

#include <cassert>
#include <filesystem>
#include <fstream>
#include <functional>

#include "utils/utils.h"
#include "compiler/ctx.h"

#include "app/cli.h"

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
#ifdef SN_WIN
  Target target = Target::Windows;
#elif defined(SN_LIN)
  Target target = Target::Linux;
#elif defined(SN_MAC)
  Target target = Target::MacOS;
#else
#error "Unknown target compiler"
#endif
#ifdef SN_X86
  Arch arch = Arch::X86;
#elif defined(SN_X86_64)
  Arch arch = Arch::X86_64;
#else
#error "Unknown architecture"
#endif
  bool static_link = false;
};

extern GlobalContext global;

} // namespace snowball

#endif // __SNOWBALL_GLOBALS_H__
