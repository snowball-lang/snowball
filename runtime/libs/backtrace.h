
#include <cstdint>
#include <cstddef>
#include <iostream>
#include <mutex>
#include <sstream>
#include <backtrace.h>

#ifndef __SNOWBALL_BACKTRACE_H_
#define __SNOWBALL_BACKTRACE_H_

#define SNOWBALL_BACKTRACE_LIMIT 21 // +1 for the eh.create function call

namespace snowball {

struct BacktraceFrame {
  const char *function;
  const char *filename;
  uintptr_t address;
  int32_t lineno;
};

struct Backtrace {
  public:
    BacktraceFrame *frames;
    int32_t frame_count;

    void push(BacktraceFrame frame);
    void push(uintptr_t address);

    void pls_free();
};

/**
 * @brief Print a backtrace of the current stack
 * @param backtrace The backtrace to print
 * @note It will only print the backtrace if `SN_BACKTRACE=1` is set
 */
void print_backtrace(Backtrace backtrace, std::ostringstream &oss);

void get_backtrace(Backtrace &backtrace);

} // namespace snowball

#endif // __SNOWBALL_BACKTRACE_H_
