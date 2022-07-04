
#include "snowball/export.hpp"
#include "snowball/types/String.h"

#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "snowball/constants.h"

extern "C" DLLEXPORT String* String__new(int8_t _, const char* string_ptr) {
    String* instance;
    instance = (struct String*)(malloc(sizeof(String)));

    instance->buffer = string_ptr;
    instance->length = strlen(string_ptr);
    instance->max_length = _SNOWBALL_MAX_LENGTH;
    instance->factor = _SNOWBALL_STR_FACTOR;

    return instance;
}
