#include <iostream>
#include <mutex>
#include <sstream>

#include "sym.h"

#ifndef _SNOWBALL_RUNTIME_H_
#define _SNOWBALL_RUNTIME_H_

#define SNOWBALL_FLAG_DEBUG (1 << 0)

namespace snowball {
extern int snowball_flags;

void initialize_exceptions();
void initialize_segfault_handler();

void error_log(std::ostringstream& oss, const char *message);
}

void initialize_snowball(int flags) __asm__("sn.runtime.initialize");
int snowball_errno() _SN_SYM("sn.runtime.errno");

#endif // _SNOWBALL_RUNTIME_H_
