module;

// Pull in command-line options and helper functions from special LLVM header
// shared by multiple LLVM tools.
#include <llvm-18/llvm/CodeGen/CommandFlags.h>
static llvm::codegen::RegisterCodeGenFlags CGF;

module cli;
import globals;

namespace snowball::app {

static cl::OptionCategory general_category("General Snowball Options");

static cl::opt<bool, true> verbose("verbose", cl::desc("Enable verbose output"), 
  cl::location(global.verbose), cl::cat(general_category),
  cl::desc("This is a verbose output that is useful for debugging and knowing target information"));
static cl::opt<bool, true> debug_verbose("debug-verbose", cl::desc("Enable debug verbose output"), 
  cl::location(global.debug_verbose), cl::cat(general_category),
  cl::desc("This is a very verbose output that is useful for debugging"));

bool ParseArguments(const Vector<String>& args) {
  return Success;
}

} // namespace snowball::app
