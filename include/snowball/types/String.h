
#include <stdint.h>
#include <stdio.h>
#include "../constants.h"

#ifndef SN_STRING_EXPORT_H
#define SN_STRING_EXPORT_H

extern "C" {

typedef struct String {
    const char * buffer;
    snowball_int_t length;
    snowball_int_t max_length;
    snowball_int_t factor; // the number of chars to preallocate when growing
} String;

}

extern "C" DLLEXPORT String* String__new_s(int8_t _, const char* string_ptr);

#endif // SN_STRING_EXPORT_H
