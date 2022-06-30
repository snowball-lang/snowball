
#include <stdint.h>
#include <stdio.h>
#include "../export.hpp"

#ifndef SN_NUMBER_NUMBER_EXPORT_H
#define SN_NUMBER_NUMBER_EXPORT_H

namespace snowball {
    class Number {
        public:
            Number(uint64_t p_number) {
                number_ptr = p_number;
            }

            Number* __sum(uint64_t s) {
                return new Number((uint64_t)((int)this->number_ptr + (int)s));
            };

        private:
            uint64_t number_ptr = 0;
    };
}

extern "C" DLLEXPORT snowball::Number* Number__new(uint64_t n);
extern "C" DLLEXPORT snowball::Number* Number__sum(snowball::Number* number, uint64_t s);

#endif // SN_NUMBER_NUMBER_EXPORT_H
