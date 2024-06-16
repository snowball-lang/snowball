
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

enum class ExplicitBitness {
  None,
  Bit32,
  Bit64
};

enum class FloatABI {
  Default,
  Soft,
  SoftFP,
  Hard
};

struct GlobalContext {
  bool verbose = false;
  bool debug_verbose = false;

  utils::TimerType timer_type = utils::TimerType::None;

  // Build options
  EmitType emit_type = EmitType::Executable;
  OptLevel opt_level = OptLevel::Debug;

  unsigned num_threads = 0;

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
  std::vector<std::string> link_flags;
  ExplicitBitness explicit_bitness = ExplicitBitness::None;
  FloatABI float_abi = FloatABI::Default;

  bool debug_opt() const {
    return opt_level == OptLevel::Debug || opt_level == OptLevel::ReleaseWithDebug;
  }

  bool emit_is_object() const {
    return emit_type == EmitType::Executable || emit_type == EmitType::Object
          || emit_type == EmitType::LlvmBc || emit_type == EmitType::Asm
          || emit_type == EmitType::Llvm;
  }
};

extern GlobalContext global;

} // namespace snowball

#endif // __SNOWBALL_GLOBALS_H__
