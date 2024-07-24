
#include "reky/reky.h"
#include "common/stl.h"
#include "common/utility/format.h"

#include "common/utility/assert.h"

// Rust generated code.
#include "rust/cxx.h"
#include "reky/src/lib.rs.h"

using namespace snowball::utils;
namespace snowball::reky {

Reky::Reky() {
  static bool mInstalled = false;
  SNOWBALL_RELEASE_ASSERT(!mInstalled, "Reky is already installed! "
    "Please use `GetRekyManager()` to get the reky manager.");
  mInstalled = true;
}

auto Reky::Execute() -> bool {
  try {
    auto modules = snowball::lib_reky_entry();
    return Success;
  } catch (const rust::Error& e) {
    FatalError(Format("Failed to execute reky: {}", e.what()));
  }
}

auto GetRekyManager() -> Reky& {
static Reky reky;
  return reky;
}

}; // namespace snowball::reky
