
#include <cstdlib>
#include <cstdint>

#include "../api.h"
#include "../constants.h"

#ifndef SN_GC_EXPORT_H
#define SN_GC_EXPORT_H

void register_gc(snowball::SNAPI* API);

extern "C" DLLEXPORT void* gc__allocate(uint32_t bytes);
extern "C" DLLEXPORT void* gc__reallocate(void* ptr, uint32_t bytes);

#endif // SN_GC_EXPORT_H
