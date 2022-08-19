
#include <stdint.h>
#include <stdio.h>
#include <sstream>

#include "../constants.h"
#include "String.h"
#include "../snowball.h"

#ifndef SN_BOOL_EXPORT_H
#define SN_BOOL_EXPORT_H

extern "C" String* __sn_bool__str(int self);
void register_bool(snowball::SNAPI* API);

#endif // SN_BOOL_EXPORT_H
