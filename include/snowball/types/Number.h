
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

    static snowball_int_t __init(snowball_int_t num);

    static String* __str(snowball_int_t self);

    static Bool* __eqeq(snowball_int_t self, snowball_int_t comp);
    static Bool* __lteq(snowball_int_t self, snowball_int_t num);

    static Bool* __not(snowball_int_t self);
    static Bool* __bool(snowball_int_t self);
};

void register_number(snowball::SNAPI* API);

#endif // SN_NUMBER_EXPORT_H
