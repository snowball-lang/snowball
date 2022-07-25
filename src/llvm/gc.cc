
#include <cstdlib>
#include <cstdint>

#include <string>
#include <vector>
#include <utility>

#include "snowball/api.h"
#include "snowball/llvm/gc.h"
#include "snowball/constants.h"
#include "snowball/utils/mangle.h"

extern "C" DLLEXPORT void* _MN14__sn__alloca__A3i32P(uint32_t bytes) {
  return malloc(bytes);
}
