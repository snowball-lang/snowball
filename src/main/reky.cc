
#include "main/reky.h"
#include "common/stl.h"
#include "common/utility/format.h"

// Rust generated code.
#include "reky/src/lib.rs.h"

namespace snowball::reky {

auto Reky::Execute() -> bool {
  if (snowball::lib_reky_entry()) {
    FatalError("Failed to execute reky!");
  }
  mInstalled = true;
  return Success;
}

auto Reky::EnsureInstalled() -> void {
  if (IsInstalled()) return;
  UnreachableError("Reky is not initialized!");
}

auto Reky::IsInstalled() const -> bool {
  return mInstalled;
}

}; // namespace snowball::reky
