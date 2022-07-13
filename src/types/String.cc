
#include "snowball/export.hpp"
#include "snowball/types/String.h"

#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "snowball/constants.h"

extern "C" DLLEXPORT String* String__init_s(const char* string_ptr) {
    String* instance;
    instance = (struct String*)(malloc(sizeof(String*) + (sizeof(string_ptr) + 1)));

    instance->buffer = string_ptr;
    instance->length = strlen(string_ptr);

    return instance;
}

extern "C" DLLEXPORT String* String__sum_String(String* self, String* sum) {

    char *result = (char*)malloc(self->length + sum->length + 1); // +1 for the null-terminator
    // in real code you would check for errors in malloc here
    strcpy(result, self->buffer);
    strcat(result, sum->buffer);

    return String__init_s(result);
}
