
#include "main/cli.h"
#include "common/stl.h"
#include "common/globals.h"
#include "common/error.h"
#include "common/utility/format.h"

#include <llvm/CodeGen/CommandFlags.h>
#include <llvm/Support/CommandLine.h>

using namespace snowball::utils;

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
  auto argsCopy = args;
  InitializeVersion();
  PrepareCommandOptions(command);
  bool commandFailed = true;
  if (!AssignCommandName(command)) {
    // We dont want to parse the command again
    argsCopy.erase(argsCopy.begin());
    commandFailed = false;
  }
  auto success = ExecuteCommandParsing(argsCopy);
  // If the command failed but we parsed the arguments successfully, then
  // the command was not found. We do this because we want the first argument
  // to be "--help" and ExecuteCommandParsing will exit if it finds that.
  if (commandFailed) {
    FatalError(Format("Command '{}' not found!", command));
  }
  return !success;
}

}; // namespace snowball::app
