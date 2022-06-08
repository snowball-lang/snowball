
#include "snowball/builtins/Number.h"
#include <stdint.h>

snowball::Number* create_number(uint64_t n) {
    return new snowball::Number( n );
}
