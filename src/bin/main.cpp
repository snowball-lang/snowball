
#ifndef SNOWBALL_CRASH_HANDLER
#define Main main
#else
#error "TODO: Implement crash handler."
#endif

#include "common/ffi.h"

import app;
using namespace snowball::app;

SN_EXTERN_START

/// @brief The entry point of the application.
int SN_API Main(int argc, char* argv[]) {
  return Application::Run(argc, argv);
}

SN_EXTERN_END

