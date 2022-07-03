
#include <stdint.h>
#include <stdio.h>
#include "../export.hpp"

#ifndef SN_NUMBER_NUMBER_EXPORT_H
#define SN_NUMBER_NUMBER_EXPORT_H

extern "C" {

typedef struct Number {
  int64_t number;
} Number;

}

extern "C" DLLEXPORT Number* Number__new(int64_t n);
extern "C" DLLEXPORT Number* Number__sum(Number* number, Number* s);

#endif // SN_NUMBER_NUMBER_EXPORT_H
