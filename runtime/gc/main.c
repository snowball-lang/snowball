#include <stdint.h>
#include <stdlib.h>

void* a(uint32_t bytes) __asm__("$Core::alloca");

/**
 * @brief Allocate bytes and return it as a pointer. \
 *        called inside the LLVM IR code.
 */
void* a(uint32_t bytes) {
  return malloc(bytes);
}