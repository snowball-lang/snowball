
#pragma once

#include "common/stl.h"

namespace snowball {
namespace app {

/// @brief The main application class.
/// It takes control of the application process. It is responsible for
/// initializing the CLI, running the package manager, and cleaning up,
/// etc.
class App {
public:
  App(int argc, char** argv);
  /// @brief Run the application process as main entry point.
  [[nodiscard]] int Run();
private:
  Vector<const char*> mArgv;
};

};
};
