#include <iostream>
#include <mutex>
#include <sstream>

#ifndef _SNOWBALL_RUNTIME_H_
#define _SNOWBALL_RUNTIME_H_

namespace snowball {
    void initialize_exceptions();
    void initialize_segfault_handler();

    void error_log(std::ostringstream& oss, const char *message);
}

void initialize_snowball() __asm__("sn.runtime.initialize");

#endif // _SNOWBALL_RUNTIME_H_
