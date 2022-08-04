
#include <stdint.h>
#include <stdio.h>
#include <sstream>

#include "../constants.h"
#include "./String.h"
#include "../snowball.h"

#ifndef SN_NUMBER_EXPORT_H
#define SN_NUMBER_EXPORT_H

extern "C" struct Number {
    snowball_int_t __number;

    static Number* __init(snowball_int_t num) {
        Number* instance;
        instance = (Number*)(malloc(sizeof(Number)));
        instance->__number = num;

        return instance;
    }

    static Number* __sum(Number* self, Number* num) {
        return __init(self->__number + num->__number);
    }

    static String* __str(Number* self) {
        std::ostringstream s;
        s << (int)self->__number;

        return String::__init(s.str().c_str());
    }
};

void register_number(snowball::SNAPI* API);

#endif // SN_NUMBER_EXPORT_H
