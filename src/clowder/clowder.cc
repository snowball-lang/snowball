
#include "clowder/clowder.h"
#include "common/stl.h"
#include "common/disk.h"

#include "common/utility/format.h"
#include "common/utility/assert.h"

#include "common/globals.h"

// Rust generated code.
#include "rust/cxx.h"
#include "clowder/src/lib.rs.h"

using namespace snowball::utils;
namespace snowball::clowder {

ClowderManager::ClowderManager() {
  static bool mInstalled = false;
  SNOWBALL_RELEASE_ASSERT(!mInstalled, "Clowder is already installed! "
    "Please use `GetClowderManager()` to get the Clowder manager.");
  mInstalled = true;
}

auto ClowderManager::Execute() -> bool {
  PrepareContext();
  try {
    auto modules = clowder::lib_clowder_entry(mContext.value());
    return Success;
  } catch (const rust::Error& e) {
    FatalError(Format("Failed to execute clowder: {}", e.what()));
  }
}

auto ClowderManager::PrepareContext() -> void {
  mContext = Context {
    .home = GetHomeDirectory().string(),
    .workspace = GetWorkspaceDirectory(WorkspaceDirectory::Dependencies)
      .string(),
    .debug = opts::IsVerbose(),
  };
}

auto GetClowderManager() -> ClowderManager& {
  static ClowderManager clowder;
  return clowder;
}

}; // namespace snowball::clowder
