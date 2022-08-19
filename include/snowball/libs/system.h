#include <cstdlib>
#include <cstdint>

#include "../api.h"
#include "../constants.h"

#ifndef SN_SYSTEM_EXPORT_H
#define SN_SYSTEM_EXPORT_H

extern "C" void __sn_system_println(String* __msg);
extern "C" void __sn_system_print(String* __msg);

namespace snowball {
    ScopeValue* sn_system_export(SNAPI* API);
}

#endif // SN_SYSTEM_EXPORT_H