
#include "snowball/types/Number.h"

#include <stdio.h>
#include <stdint.h>

snowball::Number* create_number(uint64_t n) {
    printf("num:");
    return new snowball::Number( n );
}
