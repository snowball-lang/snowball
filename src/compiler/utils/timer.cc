
#include "compiler/utils/timers.h"
#include "compiler/utils/logger.h"
#include "compiler/utils/utils.h"

namespace snowball {
namespace utils {

void Timer::start(const std::string& name, bool important) {
  times_start.push_back({name, {std::chrono::high_resolution_clock::now(), important}});
}

void Timer::stop(const std::string& name) {
  times_end.push_back({name, std::chrono::high_resolution_clock::now()});
}

void Timer::print_all(TimerType type) {
  Logger::status("Time", "Printing all times...");
  for (auto& [name, time] : times_start) {
    auto start = time.first;
    auto important = time.second;
    if (type == TimerType::Basic && !important) {
      continue;
    }
    auto end = std::find_if(times_end.begin(), times_end.end(), [&name](auto& pair) {
      return pair.first == name;
    })->second;
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    Logger::raw(F("\t {} -> {}ms\n", name, duration.count()));
  }
}

}
}
