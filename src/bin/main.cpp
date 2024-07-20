
#ifndef SNOWBALL_CRASH_HANDLER
#define Main main
#else
#error "TODO: Implement crash handler."
#endif

#include "common/ffi.h"

import app;
import stl;

using namespace snowball;

SN_EXTERN_START

/// @brief The entry point of the application.
int SN_API Main(i32 argc, char* argv[]) {
  return app::Application::Run(argc, argv);
}

SN_EXTERN_END

