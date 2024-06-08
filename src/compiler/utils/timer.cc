
#include "compiler/utils/timers.h"
#include "compiler/utils/logger.h"
#include "compiler/utils/utils.h"

#include "compiler/globals.h"

namespace snowball {
namespace utils {

void Timer::start(const std::string& name, bool important) {
  times_start.push_back({name, {std::chrono::high_resolution_clock::now(), important}});
}

void Timer::stop(const std::string& name) {
  times_end.push_back({name, std::chrono::high_resolution_clock::now()});
}

void Timer::print_all() {
  auto type = global.timer_type;
  Logger::status("Timings", "Printing all times...");
  Logger::raw("\n");
  int longest_name = 0;
  for (auto& [name, time] : times_start) {
    longest_name = std::max(longest_name, (int)name.size());
  }
  unsigned int average = 0;
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
    average += duration.count();
  }
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
    std::string spacing(longest_name - name.size(), ' ');
    fmt::terminal_color color = fmt::terminal_color::bright_green;
    if ((unsigned)duration.count() > average / times_start.size()) {
      color = fmt::terminal_color::bright_red;
    } else if ((unsigned)duration.count() > average / times_start.size() / 2) {
      color = fmt::terminal_color::bright_yellow;
    }
    Logger::raw(F("\t    {} {}= {}\n", name, spacing, fmt::styled(std::to_string(duration.count()) + "ms", fmt::fg(color) | fmt::emphasis::bold)));
  }
}

}
}
