
#include "main/app.h"
#include "common/ffi.h"
#include "common/stl.h"

SN_EXTERN_START
using namespace snowball;

auto SnowballEntry(i32 argc, const_ptr_t argv[]) -> i32 {
  return app::Application::RunAsEntry(argc, argv);
}

SN_EXTERN_END
