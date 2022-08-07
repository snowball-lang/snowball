
#include <stdint.h>
#include <stdio.h>
#include "../constants.h"
#include "snowball/api.h"

#ifndef SN_STRING_EXPORT_H
#define SN_STRING_EXPORT_H

struct Bool;

extern "C" struct String {
    const char * __buffer;
    snowball_int_t __length;

    static String* __init(const char* __str);
    static String* __sum(String* self, String* sum);
    static Bool* __eqeq(String* self, String* second);
};

void register_string(snowball::SNAPI* API);

#endif // SN_STRING_EXPORT_H
