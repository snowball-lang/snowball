
#pragma once

#include "clowder/clowder.h"
#include "common/stl.h"

namespace snowball {

/// @brief The compiler is responsible for compiling the source code
///  into whatever the target is. The compiler is in charge of
///  running clowder and the other stages of the compiler.
class Compiler final {
public:
  /// @brief Execute the compiler.
  /// @return The exit code of the compiler.
  auto Execute() -> bool;
private:
  /// @brief Execute and collect the output of the clowder command.
  auto ExecuteClowder() -> bool;
  /// @brief Start a pre-compilation step.
  auto ExecutePreCompile() -> bool;
};

}; // namespace snowball
