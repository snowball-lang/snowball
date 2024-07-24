
#pragma once

#include "common/stl.h"
#include "common/error.h"

namespace snowball {
namespace reky {

/// @brief Reky is snowball's package manager.
///  It fetches, and installs packages from the snowball repository.
/// It also returns package dependency trees and what we should compile.
class Reky final {
  /// @brief It ensures that the reky command is installed.
  auto EnsureInstalled() -> void;
public:
  Reky() = default;
  ~Reky() = default;

  /// @brief It executes the reky command.
  auto Execute() -> bool;

  /// @return If reky has been executed successfully.
  ///  and that it has been correctly installed.
  auto IsInstalled() const -> bool;
private:
  bool mInstalled{false};
};

}; // namespace reky
}; // namespace snowball
