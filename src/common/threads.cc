
#include "common/threads.h"

#include <thread>

namespace snowball {

auto GetNumThreads() -> u8 {
  return opts::GetNumThreads() 
    ? opts::GetNumThreads() 
    : std::thread::hardware_concurrency();
}

} // namespace snowball
