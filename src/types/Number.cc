
#include "snowball/export.hpp"
#include "snowball/types/Number.h"

#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "snowball/constants.h"

extern "C" DLLEXPORT Number* Number__init_i(snowball_int_t n){
    Number* instance;
    instance = (struct Number*)(malloc(sizeof(Number)));

    instance->number = n;

    return instance;
}

extern "C" DLLEXPORT Number* Number__sum_Number(Number* number, Number* sum) {
    return Number__init_i(number->number + sum->number);
}
