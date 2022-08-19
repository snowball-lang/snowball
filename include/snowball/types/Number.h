
#include <stdint.h>
#include <stdio.h>
#include <sstream>

#include "../constants.h"
#include "String.h"
#include "Bool.h"
#include "../snowball.h"

#ifndef SN_NUMBER_EXPORT_H
#define SN_NUMBER_EXPORT_H

extern "C" snowball_int_t __sn_number__init(snowball_int_t num);
extern "C" String*        __sn_number__str (snowball_int_t num);
extern "C" int            __sn_number__bool(snowball_int_t self);

void register_number(snowball::SNAPI* API);

#endif // SN_NUMBER_EXPORT_H
