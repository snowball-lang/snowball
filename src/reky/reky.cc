
#include "reky/reky.h"
#include "common/stl.h"
#include "common/disk.h"

#include "common/utility/format.h"
#include "common/utility/assert.h"

// Rust generated code.
#include "rust/cxx.h"
#include "reky/src/lib.rs.h"

using namespace snowball::utils;
namespace snowball::reky {

RekyManager::RekyManager() {
  static bool mInstalled = false;
  SNOWBALL_RELEASE_ASSERT(!mInstalled, "Reky is already installed! "
    "Please use `GetRekyManager()` to get the reky manager.");
  mInstalled = true;
}

auto RekyManager::Execute() -> bool {
  PrepareContext();
  try {
    auto modules = reky::lib_reky_entry(mContext.value());
    return Success;
  } catch (const rust::Error& e) {
    FatalError(Format("Failed to execute reky: {}", e.what()));
  }
}

auto RekyManager::PrepareContext() -> void {
  mContext = Context {
    .home = GetHomeDirectory().string(),
    .workspace = GetWorkspaceDirectory(WorkspaceDirectory::Dependencies)
      .string(),
  };
}

auto GetRekyManager() -> RekyManager& {
  static RekyManager reky;
  return reky;
}

}; // namespace snowball::reky
