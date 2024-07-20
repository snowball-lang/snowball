module;
module app;

namespace snowball::app {

Application::Application(int argc, char* argv[]) {
  mArguments.reserve(argc);
  for (int i = 0; i < argc; ++i) {
    mArguments.push_back(argv[i]);
  }
}

bool Application::RunAsMain() {
  return true;
}

bool Application::Run(int argc, char* argv[]) {
  Application app(argc, argv);
  return app.RunAsMain();
}

} // namespace snowball::app
