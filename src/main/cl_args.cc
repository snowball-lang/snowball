
#include "common/stl.h"
#include "common/globals.h"

// Pull in command-line options and helper functions from special LLVM header
// shared by multiple LLVM tools.
#include <llvm/CodeGen/CommandFlags.h>

#include <llvm/Support/CommandLine.h>
#include <llvm/Target/TargetOptions.h>
#include <llvm/Target/TargetMachine.h>

static llvm::codegen::RegisterCodeGenFlags CGF;
using namespace llvm;

namespace snowball {

GlobalContext gContext = GlobalContext();

template <typename ...Args>
using CliOpt = cl::opt<Args..., true>;

static cl::OptionCategory gGeneralCategory("General Snowball Options");

static CliOpt<bool> gVerbose("verbose", cl::desc("Enable verbose output"), 
  cl::location(gContext.mVerbose), cl::cat(gGeneralCategory),
  cl::desc("This is a verbose output that is useful for debugging and knowing target information"));
  
static CliOpt<bool> gDebugVerbose("debug-verbose", cl::desc("Enable debug verbose output"), 
  cl::location(gContext.mDebugVerbose), cl::cat(gGeneralCategory),
  cl::desc("This is a very verbose output that is useful for debugging"));

}; // namespace snowball
