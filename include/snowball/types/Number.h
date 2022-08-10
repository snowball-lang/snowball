
#include <stdint.h>
#include <stdio.h>
#include <sstream>

#include "../constants.h"
#include "String.h"
#include "Bool.h"
#include "../snowball.h"

#ifndef SN_NUMBER_EXPORT_H
#define SN_NUMBER_EXPORT_H

extern "C" struct Number {
    snowball_int_t __number;

    static Number* __init(snowball_int_t num);
    static Number* __init(Number* num);

    static Number* __sum(Number* self, Number* num);
    static String* __str(Number* self);

    static Bool* __eqeq(Number* self, Number* comp);
    static Bool* __bool(Number* self);

    static Bool* __not(Number* self);
};

void register_number(snowball::SNAPI* API);

#endif // SN_NUMBER_EXPORT_H
