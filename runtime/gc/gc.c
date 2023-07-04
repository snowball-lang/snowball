#include <stdint.h>
#include <stdlib.h>

#include "gc.h"

/**
 * @brief Allocate bytes and return it as a pointer. \
 *        called inside the LLVM IR code.
 */
void* sn_alloca(int bytes) {
  return malloc(bytes);
}

void* sn_realloc(void* object, int bytes) {
  return realloc(object, bytes);
}