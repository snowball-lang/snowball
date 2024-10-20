
#pragma once

#include "clowder/clowder.h"

#include "common/stl.h"
#include "common/timer.h"

#include "frontend/driver.h"

#define TIMER_ID "Compiler"

namespace snowball {

/// @brief The compiler is responsible for compiling the source code
///  into whatever the target is. The compiler is in charge of
///  running clowder and the other stages of the compiler.
class Compiler final : public TimedProcess, public NonCopyable {
public:
  /// @brief Execute the compiler.
  /// @return The exit code of the compiler.
  static auto Execute() -> bool;

  /// @brief Get the compiler instance.
  /// @return The compiler instance.
  static auto Singleton() -> Compiler&;
private:
  explicit Compiler() : TimedProcess(TIMER_ID) {}
  ~Compiler() = default;

  /// @brief Execute the main compiler process synchronously.
  /// The compiler uses multiple threads to compile the source code,
  ///  but this function waits for the compilation to finish.
  /// @return The exit code of the compiler.
  auto SyncCompile() -> bool;

  /// @brief Execute and collect the output of the clowder command.
  auto ExecuteClowder() -> bool;
  /// @brief Start a pre-compilation step.
  auto ExecutePreCompile() -> bool;
  /// @brief It compiles each module into a single binary or whatever
  ///  the target is.
  auto ExecuteCompile() -> bool;
  /// @brief It creates post-compilation processes.
  auto ExecutePostCompile() -> bool;

  // - Compiler stages.
  /// @brief Execute the front-end compiler.
  auto ExecuteFrontendCompiler() -> Vector<frontend::ModulePtr>; 

  /// @brief packages found by clowder.
  Vector<clowder::Package> mPackages;
};

#undef TIMER_ID

}; // namespace snowball
