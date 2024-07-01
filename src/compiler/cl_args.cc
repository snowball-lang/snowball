
#include "compiler/utils/timers.h"

#undef F
#include <llvm/Support/CommandLine.h>
#include <llvm/Target/TargetOptions.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/ADT/Optional.h>
#define SNOWBALL_UTILS_REDEFINE_F__
#include "compiler/utils/utils.h"

#include "compiler/globals.h"

// Pull in command-line options and helper functions from special LLVM header
// shared by multiple LLVM tools.
#include <llvm/CodeGen/CommandFlags.h>
static llvm::codegen::RegisterCodeGenFlags CGF;

namespace snowball {
GlobalContext global = {};

namespace opts {
namespace cl = llvm::cl;

static cl::OptionCategory general_category("General Snowball Options");

static cl::opt<bool, true> verbose("verbose", cl::desc("Enable verbose output"), 
  cl::location(global.verbose), cl::cat(general_category),
  cl::desc("This is a verbose output that is useful for debugging and knowing target information"));
static cl::opt<bool, true> debug_verbose("debug-verbose", cl::desc("Enable debug verbose output"), 
  cl::location(global.debug_verbose), cl::cat(general_category),
  cl::desc("This is a very verbose output that is useful for debugging"));

static cl::opt<utils::TimerType, true> timer_type("timer", cl::desc("Timer type"), cl::values(
  clEnumValN(utils::TimerType::Full, "full", "Full timer"),
  clEnumValN(utils::TimerType::Basic, "basic", "Basic timer"),
  clEnumValN(utils::TimerType::None, "none", "No timer")
), cl::cat(general_category), cl::location(global.timer_type), cl::init(utils::TimerType::None),
  cl::desc("This is a timer that shows each step of the compilation process"),
  cl::value_desc("type"));

// Build options
static cl::OptionCategory build_category("Build Options");

static cl::opt<EmitType, true> emit_type("emit", cl::desc("Emit type"), cl::values(
  clEnumValN(EmitType::Llvm, "llvm-ir", "LLVM IR"),
  clEnumValN(EmitType::Asm, "asm", "Assembly"),
  clEnumValN(EmitType::Object, "obj", "Object file"),
  clEnumValN(EmitType::Executable, "exec", "Executable file"),
  clEnumValN(EmitType::Ast, "ast", "Abstract Syntax Tree"),
  clEnumValN(EmitType::Sil, "sil", "Snowball Intermediate Language"),
  clEnumValN(EmitType::LlvmBc, "llvm-bc", "LLVM Bitcode")
), cl::cat(build_category), cl::location(global.emit_type), cl::init(EmitType::Executable),
  cl::desc("This is the type of output that will be generated"),
  cl::value_desc("type"));

static cl::opt<OptLevel, true> opt_level("opt", cl::desc("Optimisation level"), cl::values(
  clEnumValN(OptLevel::Debug, "debug", "Debug"),
  clEnumValN(OptLevel::Release, "release", "Release"),
  clEnumValN(OptLevel::ReleaseFast, "release-fast", "Release fast"),
  clEnumValN(OptLevel::ReleaseWithDebug, "release-with-debug", "Release with debug")
), cl::cat(build_category), cl::location(global.opt_level),
  cl::init(OptLevel::Debug), cl::value_desc("level"));

static cl::opt<unsigned, true> num_threads("threads", cl::desc("Number of threads"), 
  cl::cat(build_category), cl::location(global.num_threads), 
  cl::desc("0 means use all available threads and 1 means single-threaded"),
  cl::init(0), cl::value_desc("N"));

// Output options
static cl::OptionCategory output_category("Output Options");

static cl::opt<Target, true> target("target", cl::desc("Target OS"), cl::values(
  clEnumValN(Target::Windows, "windows", "Windows"),
  clEnumValN(Target::Linux, "linux", "Linux"),
  clEnumValN(Target::MacOS, "macos", "macOS")
), cl::cat(output_category), cl::location(global.target));

static cl::opt<Arch, true> arch("arch", cl::desc("Architecture"), cl::values(
  clEnumValN(Arch::X86_64, "x86_64", "x86_64"),
  clEnumValN(Arch::Arm64, "arm64", "Arm64")
), cl::cat(output_category), cl::location(global.arch));

static cl::opt<bool, true> static_link("static", cl::desc("Static linkage"), 
  cl::cat(output_category), cl::location(global.static_link),
  cl::desc("This is a flag that determines whether the output will be statically linked"));

static cl::list<std::string, std::vector<std::string>> link_flags("z", 
  cl::desc("Flags to pass to the linker.\nEvery instance of -L will be passed to the linker\nIt can be comma separated too"), cl::cat(output_category),
  cl::location(global.link_flags), cl::ZeroOrMore, cl::CommaSeparated,
  cl::Prefix);

static cl::opt<ExplicitBitness, true> explicit_bitness("explicit-bitness", cl::desc("Explicit bitness"), cl::values(
  clEnumValN(ExplicitBitness::None, "none", "None"),
  clEnumValN(ExplicitBitness::Bit32, "32", "32-bit"),
  clEnumValN(ExplicitBitness::Bit64, "64", "64-bit")
), cl::cat(output_category), cl::location(global.explicit_bitness), cl::init(ExplicitBitness::None),
  cl::desc("This is a flag that determines the bitness of the output"),
  cl::value_desc("bitness"));

static cl::opt<bool, true> disable_virtual_call_opt("disable-devirtualization", cl::desc("Disable virtual call optimisation"), 
  cl::cat(output_category), cl::location(global.disable_virtual_call_opt),
  cl::desc("This is a flag that determines whether the virtual call optimisation will be disabled"));

} // namespace opts
} // namespace snowball

