#include <cstdlib>
#include <cstdint>

#include "../api.h"
#include "../constants.h"

#ifndef SN_SYSTEM_EXPORT_H
#define SN_SYSTEM_EXPORT_H

extern "C" struct System {
    static void println(String* __msg) {
        printf("%s\n", __msg->__buffer);
    }

    static void print(String* __msg) {
        printf("%s\n", __msg->__buffer);
    }
};

namespace snowball {
    ScopeValue* sn_system_export(SNAPI* API);
}

#endif // SN_SYSTEM_EXPORT_H