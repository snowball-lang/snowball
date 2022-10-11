
#include <stdint.h>
#include <stdio.h>
#include "../constants.h"
#include "snowball/api.h"
#include "snowball/types.h"

#ifndef SN_STRING_EXPORT_H
#define SN_STRING_EXPORT_H

struct String {
    static int _bool(char* self);
    static int _eqeq(char* self, char* second);
    static char* _sum(char* self, char* sum);
};

void register_string(snowball::SNAPI* API);

#endif // SN_STRING_EXPORT_H
