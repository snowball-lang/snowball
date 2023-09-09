#include <stdint.h>
#include <stdlib.h>

#include "gc.h"

/**
 * @brief Allocate bytes and return it as a pointer. \
 *        called inside the LLVM IR code.
 * @param bytes The number of bytes to allocate.
 */
void* sn_alloca(size_t bytes) {
  if (bytes == 0) 
    bytes = 1; // Allocate at least 1 byte.

  return malloc(bytes);
}

void* sn_realloc(void* object, int bytes) {
  return realloc(object, bytes);
}