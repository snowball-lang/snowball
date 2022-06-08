
#include <stdint.h>

#ifndef SN_NUMBER_NUMBER_EXPORT_H
#define SN_NUMBER_NUMBER_EXPORT_H

namespace snowball {
    class Number {
        public:
            Number(uint64_t p_number) : number_ptr(p_number) {};

        private:
            uint64_t number_ptr;
    };
}

extern "C" {
    snowball::Number* create_number(uint64_t n);
}

#endif // SN_NUMBER_NUMBER_EXPORT_H
