
#include "common/timer.h"
#include "common/utility/assert.h"
#include "common/utility/logger.h"

using namespace snowball::utils;

namespace snowball {

TimedProcess::TimedProcess(const String& name) : mName(name) {
  timers::CreateTimer(name);
}

namespace {
static Map<String, chrono::TimePoint> gTimers{};

static auto AssertTimerExists(const String& name) -> void {
  SNOWBALL_ASSERT(gTimers.find(name) != gTimers.end(), 
      "Timer does not exist.");
}

}; // namespace

auto timers::CreateTimer(const String& name) -> void {
  SNOWBALL_ASSERT(gTimers.find(name) == gTimers.end(), 
      "Timer already exists.");
  gTimers[name] = chrono::HighResClock::now();
}

auto timers::StartTimer(const String& name) -> void {
  AssertTimerExists(name);
  GetLogger().Debug(Format("Starting timer: {}", name));
  gTimers[name] = chrono::HighResClock::now();
}

auto timers::StopTimer(const String& name) -> void {
  AssertTimerExists(name);
  GetLogger().Debug(Format("Stopping timer: {}", name));
  gTimers[name] = chrono::HighResClock::now();
}

auto timers::GetTimeElapsed(const String& name) -> f64 {
  AssertTimerExists(name);
  auto start = gTimers[name];
  auto end = chrono::HighResClock::now();
  auto duration = chrono::Duration(end - start);
  return duration.count();
}

auto timers::ClearTimer(const String& name) -> void {
  AssertTimerExists(name);
  gTimers.erase(name);
}

}; // namespace snowball
