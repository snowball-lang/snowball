
#include "runtime.h"

void initialize_snowball() {
    snowball::initialize_segfault_handler();
    snowball::initialize_exceptions();
}

namespace snowball {
void error_log(std::ostringstream& oss, const char *message) {
    oss << "\n\n\e[1;31merror\e[1;37m: " << message;
}
}
