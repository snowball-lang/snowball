
#include <stdint.h>
#include <stdio.h>
#include "../constants.h"
#include "snowball/api.h"

#ifndef SN_STRING_EXPORT_H
#define SN_STRING_EXPORT_H

extern "C" {

typedef struct String {
    const char * buffer;
    snowball_int_t length;
} String;

}

void register_string(snowball::SNAPI* API);

extern "C" DLLEXPORT String* _MN6StringN6__initA1sP(const char* string_ptr);
extern "C" DLLEXPORT String* _MN6StringN5__sumA6StringA6StringP(String* self, String* sum);

#endif // SN_STRING_EXPORT_H
