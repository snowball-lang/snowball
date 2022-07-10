
#include <cstdlib>
#include <cstdint>

#include "snowball/llvm/gc.h"
#include "snowball/constants.h"

extern "C" DLLEXPORT void* gc__allocate(uint32_t bytes) {
  return malloc(bytes);
}

extern "C" DLLEXPORT void* gc__reallocate(void* ptr, uint32_t bytes) {
  return realloc(ptr, bytes);
}
