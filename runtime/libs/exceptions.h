
#ifndef _SNOWBALL_RUNTIME_EXCEPTIONS_H_
#define _SNOWBALL_RUNTIME_EXCEPTIONS_H_

#include "backtrace.h"

namespace snowball {
uint64_t exception_class();
int64_t exception_offset();
};

#endif // _SNOWBALL_RUNTIME_EXCEPTIONS_H_
