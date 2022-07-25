
#include <stdint.h>
#include <stdio.h>
#include "../constants.h"
#include "snowball/api.h"

#ifndef SN_STRING_EXPORT_H
#define SN_STRING_EXPORT_H

extern "C" struct String {
    const char * __buffer;
    snowball_int_t __length;

    static String* __init(const char* __str) {
        String* instance;
        instance = (struct String*)(malloc(sizeof(String*) + (sizeof(__str) + 1)));

        instance->__buffer = __str;
        instance->__length = strlen(__str);

        return instance;
    }

    static String* __sum(String* self, String* sum) {

        char *result = (char*)malloc(self->__length + sum->__length + 1); // +1 for the null-terminator
        // in real code you would check for errors in malloc here
        strcpy(result, self->__buffer);
        strcat(result, sum->__buffer);

        return __init(result);
    }
};

void register_string(snowball::SNAPI* API);

#endif // SN_STRING_EXPORT_H
