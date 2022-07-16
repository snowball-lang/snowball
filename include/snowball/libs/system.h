#include <cstdlib>
#include <cstdint>

#include "../api.h"
#include "../constants.h"

#ifndef SN_SYSTEM_EXPORT_H
#define SN_SYSTEM_EXPORT_H

namespace snowball {
    ScopeValue* sn_system_export(SNAPI* API);
}

extern "C" DLLEXPORT void _MN6SystemN5printA6StringP(String* str);
extern "C" DLLEXPORT void _MN6SystemN7printlnA6StringP(String* str);

#endif // SN_SYSTEM_EXPORT_H