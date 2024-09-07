
#include "common/threads.h"
#include "common/utility/assert.h"

#include <thread>

namespace snowball {

auto GetNumThreads() -> u8 {
  return opts::GetNumThreads() 
    ? opts::GetNumThreads() 
    : std::thread::hardware_concurrency();
}

auto ThreadPoolExecutor(usize numTimes, Function<void(usize)> func, 
    u8 numThreads) -> void {
  SNOWBALL_ASSERT(numThreads > 0, "Number of threads must be greater than 0.");
  auto strategy = threads::HardwareStrategy(numThreads);
  threads::ThreadPool pool(strategy);
  for (usize i = 0; i < numTimes; ++i)
    pool.async(func, i);
  pool.wait();
}

} // namespace snowball
