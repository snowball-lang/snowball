
#pragma once

#include "common/stl.h"
#include "common/error.h"

#include "reky/src/lib.rs.h"

namespace snowball {
namespace reky {

/// @brief Reky is snowball's package manager.
///  It fetches, and installs packages from the snowball repository.
/// It also returns package dependency trees and what we should compile.
/// @see GetRekyManager
class RekyManager final {
public:
  RekyManager();
  ~RekyManager() = default;

  /// @brief It executes the reky command.
  auto Execute() -> bool;
  /// @brief Prepare reky's context object.
  auto PrepareContext() -> void;
private:
  static bool mInstalled;
  Opt<Context> mContext = None;
};

[[nodiscard]] auto GetRekyManager() -> RekyManager&;

}; // namespace reky
}; // namespace snowball
