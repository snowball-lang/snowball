module;

// Pull in command-line options and helper functions from special LLVM header
// shared by multiple LLVM tools.
#include <llvm-18/llvm/CodeGen/CommandFlags.h>

#include <llvm-18/llvm/Support/CommandLine.h>
#include <llvm-18/llvm/Target/TargetOptions.h>
#include <llvm-18/llvm/Target/TargetMachine.h>

static llvm::codegen::RegisterCodeGenFlags CGF;
using namespace llvm;

module globals;

namespace snowball {

GlobalContext gContext = GlobalContext();

static cl::OptionCategory gGeneralCategory("General Snowball Options");

static cl::opt<bool, true> gVerbose("verbose", cl::desc("Enable verbose output"), 
  cl::location(gContext.mVerbose), cl::cat(gGeneralCategory),
  cl::desc("This is a verbose output that is useful for debugging and knowing target information"));
  
static cl::opt<bool, true> gDebugVerbose("debug-verbose", cl::desc("Enable debug verbose output"), 
  cl::location(gContext.mDebugVerbose), cl::cat(gGeneralCategory),
  cl::desc("This is a very verbose output that is useful for debugging"));

}; // namespace snowball
