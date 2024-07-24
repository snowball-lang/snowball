
#include "main/app.h"
#include "main/cli.h"
#include "common/stl.h"

namespace snowball::app {

Application::Application(i32 argc, const_ptr_t argv[]) {
  mArguments.reserve(argc);
  for (i32 i = 0; i < argc; i++) {
    mArguments.push_back(argv[i]);
  }
  if (argc > 1) mCommand = argv[1];
  else mArguments.push_back("-h");
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
