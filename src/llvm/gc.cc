
#include <cstdlib>
#include <cstdint>

#include <string>
#include <vector>
#include <utility>

#include "snowball/api.h"
#include "snowball/llvm/gc.h"
#include "snowball/constants.h"
#include "snowball/utils/mangle.h"

/**
 * @brief Allocate bytes and return it as a pointer. \
 *        called inside the LLVM IR code.
 *
 * @note This function is already mangled to \
 *       directly access it from the dynamic library
 */
extern "C" DLLEXPORT void* _SNalc(uint32_t bytes) {
  return malloc(bytes);
}
