
#include "runtime.h"

void initialize_snowball(int flags) {
    snowball::initialize_segfault_handler();
    snowball::initialize_exceptions();

    snowball::snowball_flags = flags;
}

namespace snowball {
int snowball_flags = 0;

void error_log(std::ostringstream& oss, const char *message) {
    oss << "\n\n\e[1;31merror\e[1;37m: " << message;
}
}
