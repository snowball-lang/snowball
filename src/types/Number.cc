
#include "snowball/export.hpp"
#include "snowball/types/Number.h"

#include <stdio.h>
#include <stdint.h>

extern "C" DLLEXPORT snowball::Number* sn_create_number(uint64_t n){
    return new snowball::Number(n);
}