
#pragma once

#include "common/stl.h"
#include "common/error.h"

namespace snowball {
namespace reky {

/// @brief Reky is snowball's package manager.
///  It fetches, and installs packages from the snowball repository.
/// It also returns package dependency trees and what we should compile.
/// @see GetRekyManager
class Reky final {
public:
  Reky();
  ~Reky() = default;

  /// @brief It executes the reky command.
  auto Execute() -> bool;
private:
  static bool mInstalled;
};

auto GetRekyManager() -> Reky&;

}; // namespace reky
}; // namespace snowball
