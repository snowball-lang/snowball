
// TODO: This is a temporary solution.
// TODO: Add support for macOS.

#include "runtime.h"
#include "backtrace.h"

#include <sigsegv.h>

namespace snowball {

int segfault_handler(void *fault_address, int serious) {
    std::ostringstream buf;
    error_log(buf, "Segmentation fault");
    buf << ": \033[0mSegmentation fault at address \e[1;37m" << std::hex << (void*)fault_address << std::dec << "\e[0m";

    Backtrace base;
    get_backtrace(base);
    print_backtrace(base, buf);

    buf << "\n";
    auto output = buf.str();
    fflush(stdout);
    fwrite(output.data(), 1, output.size(), stderr);

    exit(1);
    return 0;
}

void initialize_segfault_handler() {
    sigsegv_install_handler(&segfault_handler);
    // TODO: buffer overflow, etc...
}   
}
