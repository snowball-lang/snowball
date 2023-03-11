#include <stdint.h>
#include <stdlib.h>

/**
 * @brief Allocate bytes and return it as a pointer. \
 *        called inside the LLVM IR code.
 *
 * @note This function is already mangled to \
 *       directly access it from the dynamic library
 */

void* _SNalc(uint32_t bytes) {
  return malloc(bytes);
}