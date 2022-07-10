
#include <cstdlib>
#include <cstdint>

#include "../constants.h"

#ifndef SN_GC_EXPORT_H
#define SN_GC_EXPORT_H

extern "C" DLLEXPORT void* gc__allocate(uint32_t bytes);
extern "C" DLLEXPORT void* gc__reallocate(void* ptr, uint32_t bytes);

#endif // SN_GC_EXPORT_H
