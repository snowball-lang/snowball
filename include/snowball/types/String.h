
#include <stdint.h>
#include <stdio.h>
#include "../constants.h"
#include "snowball/api.h"
#include "snowball/types.h"

#ifndef SN_STRING_EXPORT_H
#define SN_STRING_EXPORT_H

struct Bool;

extern "C" struct String {
    char * __buffer;
    snowball_int_t __length;
};

extern "C" int __sn_string__bool(String* self);
extern "C" int __sn_string__eqeq(String* self, String* second);
extern "C" String* __sn_string__init(char* __str);
extern "C" String* __sn_string__sum(String* self, String* sum);

void register_string(snowball::SNAPI* API);

#endif // SN_STRING_EXPORT_H
