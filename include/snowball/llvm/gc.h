
#include <cstdlib>
#include <cstdint>

#include "../api.h"
#include "../constants.h"

#ifndef SN_GC_EXPORT_H
#define SN_GC_EXPORT_H

void register_gc(snowball::SNAPI* API);

extern "C" DLLEXPORT void* _MN10gc__allocaA3i32P(uint32_t bytes);
extern "C" DLLEXPORT void* _MN12gc__reallocaA2i8A3i32P(void* ptr, uint32_t bytes);

#endif // SN_GC_EXPORT_H
