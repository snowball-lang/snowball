
#include "main/cli.h"

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

auto ParseCommandArgs(const CommandArgs& args, const String& command) -> bool {
  InitializeVersion();
  return ExecuteCommandParsing(args); 
}

}; // namespace snowball::app
