
#include <stdint.h>
#include <stdio.h>
#include "../constants.h"
#include "../snowball.h"

#ifndef SN_NUMBER_EXPORT_H
#define SN_NUMBER_EXPORT_H

extern "C" struct Number;

void register_number(snowball::SNAPI* API);

extern "C" DLLEXPORT Number* _MN6NumberN6__initA1iP(snowball_int_t n);
extern "C" DLLEXPORT Number* _MN6NumberN5__sumA6NumberA6NumberP(Number* number, Number* s);

#endif // SN_NUMBER_EXPORT_H
