
import app;

#ifndef SNOWBALL_CRASH_HANDLER
#define Main main
#else
#error "TODO: Implement crash handler."
#endif

using namespace snowball::app;

#ifdef __cplusplus
extern "C" {
#endif

/// @brief The entry point of the application.
int Main(int argc, char* argv[]) {
  return Application::Run(argc, argv);
}

#ifdef __cplusplus
}
#endif
