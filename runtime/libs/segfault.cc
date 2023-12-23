
// TODO: This is a temporary solution.
// TODO: Add support for macOS.

#include "runtime.h"
#include "backtracing.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>

namespace snowball {

void segfault_handler(int signal, siginfo_t *fault_info, void *arg) {
    std::ostringstream buf;
    error_log(buf, "Segmentation fault");
    buf << ": \033[0mSegmentation fault at address \e[1;37m" << std::hex << (void*)fault_info->si_addr << std::dec << "\e[0m";

    Backtrace base;
    get_backtrace(base);
    print_backtrace(base, buf);

    buf << "\n";
    auto output = buf.str();
    fflush(stdout);
    fwrite(output.data(), 1, output.size(), stderr);

    exit(1);
}

void initialize_segfault_handler() {
    struct sigaction sa;

    memset(&sa, 0, sizeof(struct sigaction));
    sigemptyset(&sa.sa_mask);
    sa.sa_sigaction = segfault_handler;
    sa.sa_flags   = SA_SIGINFO;

    sigaction(SIGSEGV, &sa, NULL);
    // TODO: buffer overflow, etc...
}   
}
