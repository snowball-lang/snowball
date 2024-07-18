
#include "main/app.h"
#include "main/cli.h"

namespace snowball::app {

App::App(int argc, char** argv) {
  mArgv.reserve(argc);
  for (int i = 0; i < argc; ++i) {
    mArgv.push_back(argv[i]);
  }
}

int App::Run() {
  if (!ParseCommandLine(mArgv)) {
    return EXIT_FAILURE;
  }
  return 0;
}

};
