
#include "compiler/utils/timers.h"

#undef F
#include <llvm/Support/CommandLine.h>
#include <llvm/Target/TargetOptions.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/ADT/Optional.h>
#define SNOWBALL_UTILS_REDEFINE_F__
#include "compiler/utils/utils.h"

#include "compiler/globals.h"
#include "app/cli.h"

// Pull in command-line options and helper functions from special LLVM header
// shared by multiple LLVM tools.
#include <llvm/CodeGen/CommandFlags.h>
static llvm::codegen::RegisterCodeGenFlags CGF;

namespace snowball {
GlobalContext* global = new GlobalContext();

namespace opts {
namespace cl = llvm::cl;

void register_globals() {
  cl::OptionCategory general_category("General Snowball Options");

  cl::opt<bool, true> verbose("verbose", cl::desc("Enable verbose output"), 
    cl::location(global.verbose), cl::init(false), cl::cat(general_category));
  cl::opt<bool, true> debug_verbose("debug-verbose", cl::desc("Enable debug verbose output"), 
    cl::location(global.debug_verbose), cl::init(false), cl::cat(general_category));

  cl::opt<utils::TimerType, true> timer_type("timer", cl::desc("Timer type"), cl::values(
    clEnumValN(utils::TimerType::Full, "full", "Full timer"),
    clEnumValN(utils::TimerType::Basic, "basic", "Basic timer"),
    clEnumValN(utils::TimerType::None, "none", "No timer")
  ), cl::cat(general_category), cl::location(global.timer_type), cl::init(utils::TimerType::None));

  // Build options
  cl::OptionCategory build_category("Build Options");

  cl::opt<EmitType, true> emit_type("emit", cl::desc("Emit type"), cl::values(
    clEnumValN(EmitType::Llvm, "llvm-ir", "LLVM IR"),
    clEnumValN(EmitType::Asm, "asm", "Assembly"),
    clEnumValN(EmitType::Object, "obj", "Object file"),
    clEnumValN(EmitType::Executable, "exec", "Executable file"),
    clEnumValN(EmitType::Ast, "ast", "Abstract Syntax Tree"),
    clEnumValN(EmitType::Sil, "sil", "Snowball Intermediate Language"),
    clEnumValN(EmitType::LlvmBc, "llvm-bc", "LLVM Bitcode")
  ), cl::cat(build_category), cl::location(global.emit_type), cl::init(EmitType::Executable));

  cl::opt<OptLevel, true> opt_level("opt", cl::desc("Optimisation level"), cl::values(
    clEnumValN(OptLevel::Debug, "debug", "Debug"),
    clEnumValN(OptLevel::Release, "release", "Release"),
    clEnumValN(OptLevel::ReleaseFast, "release-fast", "Release fast"),
    clEnumValN(OptLevel::ReleaseWithDebug, "release-with-debug", "Release with debug")
  ), cl::cat(build_category), cl::location(global.opt_level), cl::init(OptLevel::Release));

  // Output options
  cl::OptionCategory output_category("Output Options");

  cl::opt<Target, true> target("target", cl::desc("Target OS"), cl::values(
    clEnumValN(Target::Windows, "windows", "Windows"),
    clEnumValN(Target::Linux, "linux", "Linux"),
    clEnumValN(Target::MacOS, "macos", "macOS")
  ), cl::cat(output_category), cl::location(global.target), cl::init(
  #ifdef SN_WIN
    Target::Windows
  #elif defined(SN_LIN)
    Target::Linux
  #elif defined(SN_MAC)
    Target::MacOS
  #else
  #error "Unknown target compiler"
  #endif
    ));

  cl::opt<Arch, true> arch("arch", cl::desc("Architecture"), cl::values(
    clEnumValN(Arch::X86_64, "x86_64", "x86_64"),
    clEnumValN(Arch::Arm64, "arm64", "Arm64")
  ), cl::cat(output_category), cl::location(global.arch), cl::init(
  #ifdef SN_X86_64
    Arch::X86_64
  #elif defined(SN_ARM64)
    Arch::Arm64
  #else
  #error "Unknown architecture"
  #endif
    ));

  cl::opt<bool, true> static_link("static", cl::desc("Static linkage"), 
    cl::cat(output_category), cl::location(global.static_link), cl::init(false));
}

} // namespace opts
} // namespace snowball

