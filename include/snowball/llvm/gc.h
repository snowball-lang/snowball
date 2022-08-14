
#include <cstdlib>
#include <cstdint>

#include "../api.h"
#include "../constants.h"

#ifndef SN_GC_EXPORT_H
#define SN_GC_EXPORT_H

extern "C" DLLEXPORT void* _SNalc(uint32_t bytes);

#endif // SN_GC_EXPORT_H
