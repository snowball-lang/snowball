#pragma once

#include "common/stl.h"
#include "common/globals.h"

namespace snowball {
namespace timers {

/// @brief It creates a new timer instance in the static memory.
/// @return The timer instance.
auto CreateTimer(const String& name) -> void;

/// @brief Start the timer.
/// @param name The name of the timer.
auto StartTimer(const String& name) -> void;

/// @brief Stop the timer.
/// @param name The name of the timer.
auto StopTimer(const String& name) -> void;

/// @brief Clear the timer.
/// @param name The name of the timer.
auto ClearTimer(const String& name) -> void;

/// @brief Get the time elapsed in seconds.
/// @param name The name of the timer.
/// @return The time elapsed in seconds.
auto GetTimeElapsed(const String& name) -> f64;

}; // namespace timers

/// @brief Represents a compiler process that can be timed.
class TimedProcess {
public:
  /// @brief Default constructor.
  /// @param name The name of the process.
  explicit TimedProcess(const String& name);

  /// @brief Start the timer.
  auto Start() -> void { timers::StartTimer(mName); }
  /// @brief Stop the timer.
  auto Stop() -> void { timers::StopTimer(mName); }
  /// @brief Get the time elapsed in seconds.
  /// @return The time elapsed in seconds.
  auto GetTimeElapsed() -> f64 { 
    return timers::GetTimeElapsed(mName); 
  }

  /// @brief Default destructor.
  ~TimedProcess() { timers::ClearTimer(mName); }

private:
  String mName{}; ///< The name of the process.
};

}; // namespace snowball