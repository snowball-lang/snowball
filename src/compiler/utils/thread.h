
#ifndef __SNOWBALL_COMPILER_UTILS_THREAD_H__
#define __SNOWBALL_COMPILER_UTILS_THREAD_H__

#include <thread>
#include "compiler/globals.h"

namespace snowball {
namespace utils {

static size_t get_num_threads() {
  auto num_threads = global.num_threads;
  if (num_threads == 0) {
    num_threads = std::thread::hardware_concurrency();
  }
  return num_threads;
}

} // namespace utils
} // namespace snowball

#endif // __SNOWBALL_COMPILER_UTILS_THREAD_H__
