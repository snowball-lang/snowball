
#include <stdint.h>
#include <stdio.h>
#include "../constants.h"

#ifndef SN_NUMBER_EXPORT_H
#define SN_NUMBER_EXPORT_H

extern "C" {

typedef struct Number {
  snowball_int_t number;
} Number;

}

extern "C" DLLEXPORT Number* Number__init_i(snowball_int_t n);
extern "C" DLLEXPORT Number* Number__sum_n_n(Number* number, Number* s);

#endif // SN_NUMBER_EXPORT_H
