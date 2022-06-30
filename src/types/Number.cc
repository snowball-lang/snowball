
#include "snowball/export.hpp"
#include "snowball/types/Number.h"

#include <stdio.h>
#include <stdint.h>

extern "C" DLLEXPORT snowball::Number* Number__new(uint64_t n){
    return new snowball::Number(n);
}

extern "C" DLLEXPORT snowball::Number* Number__sum(snowball::Number* number, uint64_t s) {
    return number->__sum(s);
}
