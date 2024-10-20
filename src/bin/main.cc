
#include "main/app.h"
#include "common/ffi.h"
#include "common/stl.h"

using namespace snowball;
SN_EXTERN_START

auto SnowballEntry(i32 argc, const_ptr_t argv[]) -> i32 {
  return app::Application::RunAsEntry(argc, argv);
}

SN_EXTERN_END
