
#ifndef __SNOWBALL_COMPILER_UTILS_TIMERS_H__
#define __SNOWBALL_COMPILER_UTILS_TIMERS_H__

#include <chrono>
#include <string>
#include <vector>

namespace snowball {
namespace utils {

using ChronoTime = std::chrono::time_point<std::chrono::high_resolution_clock>;

enum class TimerType {
  Basic,
  Full,
  None
};

class Timer {
  template <typename T>
  using TimerPair = std::pair<std::string, T>;
  std::vector<TimerPair<std::pair<ChronoTime, bool>>> times_start;
  std::vector<TimerPair<ChronoTime>> times_end;
public:
  void start(const std::string& name, bool important = false);
  void stop(const std::string& name);
  void print_all(TimerType type = TimerType::Basic);
};

}
}
  
#endif // __SNOWBALL_COMPILER_UTILS_TIMERS_H__
