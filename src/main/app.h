
#pragma once
#include "common/stl.h"

namespace snowball {
namespace app {

/// @brief Main application entry point.
/// The first stage of the compiler is the parsing of the command line 
/// arguments and the application configuration file. The compiler uses t
/// he `llvm::cl` library to parse the command line arguments.
/// 
/// The application is in charge of initializing the CLI parser and executing 
/// the main function of the compiler. 
/// 
/// The CLI parser is responsible for parsing the command line arguments and 
/// setting the appropriate flags in the compiler.
class Application {
public:
  /// @brief Execute snowball as an entry point.
  /// @param argc The number of command line arguments.
  /// @param argv The command line arguments.
  /// @return The exit code of the application.
  static auto RunAsEntry(i32 argc, const_ptr_t argv[]) -> bool;
  /// @brief Application constructor. It translates the 
  ///  arguments into an STL vector of strings.
  /// @see RunAsEntry
  Application(i32 argc, const_ptr_t argv[]);
  /// @brief Execute the application.
  auto Run() -> bool;
private:
  String mCommand{"-h"};
  Vector<const_ptr_t> mArguments{};
};

} // namespace app
} // namespace snowball