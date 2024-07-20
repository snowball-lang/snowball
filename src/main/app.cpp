module;
module app;

import cli;

namespace snowball::app {

Application::Application(i32 argc, char* argv[]) {
  mArguments.reserve(argc);
  for (i32 i = 0; i < argc; ++i) {
    mArguments.push_back(argv[i]);
  }
}

bool Application::RunAsMain() {
  if (ParseArguments(mArguments)) {
    return Failure;
  }
  return Success;
}

bool Application::Run(i32 argc, char* argv[]) {
  Application app(argc, argv);
  return app.RunAsMain();
}

} // namespace snowball::app
