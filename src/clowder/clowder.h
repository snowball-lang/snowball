
#pragma once

#include "common/stl.h"
#include "common/error.h"

#include "clowder/src/lib.rs.h"

namespace snowball {
namespace clowder {

/// @brief clowder is snowball's package manager.
///  It fetches, and installs packages from the snowball repository.
/// It also returns package dependency trees and what we should compile.
/// @see GetClowderManager
class ClowderManager final {
public:
  ClowderManager();
  ~ClowderManager() = default;

  /// @brief It executes the clowder command.
  auto Execute() -> bool;
  /// @brief Prepare clowder's context object.
  auto PrepareContext() -> void;
  /// @brief Get the clowder's modules.
  [[nodiscard]] auto GetPackages() -> Vector<clowder::Package>; 
private:
  static bool mInstalled;
  Opt<Context> mContext{None};

  Vector<clowder::Package> mPackages;
};

[[nodiscard]] auto GetClowderManager() -> ClowderManager&;

}; // namespace clowder
}; // namespace snowball
