
#include "main/cli.h"
#include "common/stl.h"
#include "common/globals.h"

#include <llvm/CodeGen/CommandFlags.h>
#include <llvm/Support/CommandLine.h>

namespace snowball::app {

static auto InitializeVersion() -> void {
  llvm::cl::SetVersionPrinter([](llvm::raw_ostream& os) {
    os << "Snowball Compiler";
    os << " - Version 0.1.0\n";
  });
}

static auto ExecuteCommandParsing(const CommandArgs& args) -> bool {
  return llvm::cl::ParseCommandLineOptions(args.size(), args.data(), 
    "Snowball Compiler", nullptr, nullptr, false);
}

static auto PrepareCommandOptions(const String& command) -> void {
  if (command == "-h" || command == "--help") {
    // add "run", "build", "test" commands
    new llvm::cl::SubCommand("run", "Run the Snowball Compiler");
    new llvm::cl::SubCommand("build", "Build the Snowball Compiler");
    new llvm::cl::SubCommand("test", "Test the Snowball Compiler");
  }
};

static auto AssignCommandName(const String& command) -> bool {
  if (command == "run") {
    gContext.mCommand = Command::Run;
    return Success;
  } else if (command == "build") {
    gContext.mCommand = Command::Build;
    return Success;
  }
  return Failure;
}

auto ParseCommandArgs(const CommandArgs& args, const String& command) -> bool {
  InitializeVersion();
  PrepareCommandOptions(command);
  auto success = ExecuteCommandParsing(args);
  return success && AssignCommandName(command);
}

}; // namespace snowball::app
