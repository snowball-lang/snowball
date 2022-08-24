
#include <stdint.h>
#include <stdio.h>
#include "../constants.h"
#include "snowball/api.h"
#include "snowball/types.h"

#ifndef SN_STRING_EXPORT_H
#define SN_STRING_EXPORT_H

extern "C" int sn_String__bool(char* self);
extern "C" int sn_String__eqeq(char* self, char* second);
extern "C" char* sn_String__sum(char* self, char* sum);

void register_string(snowball::SNAPI* API);

#endif // SN_STRING_EXPORT_H
