
#include <stdint.h>
#include <stdio.h>
#include <sstream>

#include "../constants.h"
#include "String.h"
#include "../snowball.h"

#ifndef SN_BOOL_EXPORT_H
#define SN_BOOL_EXPORT_H

struct Number;

extern "C" struct Bool {
    bool __bool;

    static Bool* __init(bool value);
    static Bool* __init(snowball_int_t value);
    static snowball_int_t __real_bool(Bool* self);
    static String* __str(Bool* self);
    static Bool* __not(Bool* self);
    static Bool* __eqeq(Bool* self, Bool* second);
};

void register_bool(snowball::SNAPI* API);

#endif // SN_BOOL_EXPORT_H
