#include <stdint.h>
#include <stdlib.h>

extern void* snAlloca(uint32_t bytes) __asm__("Core::alloca");

/**
 * @brief Allocate bytes and return it as a pointer. \
 *        called inside the LLVM IR code.
 */
void* snAlloca(uint32_t bytes) {
  return malloc(bytes);
}