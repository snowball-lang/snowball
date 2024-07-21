
#include "main/app.h"
#include "main/cli.h"
#include "common/stl.h"

namespace snowball::app {

Application::Application(i32 argc, const_ptr_t argv[]) {
  auto extraArgs = (argc <= 2 ? 0 : 1);
  mArguments.reserve(argc);
  mCommand = argv[1];
  for (i32 i = extraArgs; i < argc; i++) {
    mArguments.push_back(argv[i]);
  }
}

auto Application::Run() -> bool {
  if (ParseCommandArgs(mArguments, mCommand)) {
    return Failure;
  }
  return Success;
}

auto Application::RunAsEntry(i32 argc, const_ptr_t argv[]) -> bool {
  Application app(argc, argv);
  return app.Run();
}

}; // namespace snowball::app
