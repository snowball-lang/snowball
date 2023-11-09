
#include "runtime.h"

void initialize_snowball() {
#ifndef __APPLE__ // TODO: Add support for macOS.
    snowball::initialize_segfault_handler();
#endif
    snowball::initialize_exceptions();
}

namespace snowball {
void error_log(std::ostringstream& oss, const char *message) {
    oss << "\n\n\e[1;31merror\e[1;37m: " << message;
}
}
