
#include "common/stl.h"
#include "common/disk.h"

#include "common/error.h"

namespace snowball {

auto GetSnowballDirectory() -> fs::Path {
  return fs::current_path() / ".sn";
}

auto GetHomeDirectory() -> fs::Path {
  if (const_ptr_t home = std::getenv("SNOWBALL_HOME")) {
    return fs::Path(home);
  }
  return fs::Path(std::getenv("HOME")) / ".snowball";
}

auto GetWorkspaceDirectory(WorkspaceDirectory directory) -> fs::Path {
  switch (directory) {
    case WorkspaceDirectory::Dependencies:
      return GetSnowballDirectory() / "deps";
    case WorkspaceDirectory::Build:
      return GetSnowballDirectory() / "build";
    case WorkspaceDirectory::Bin:
      return GetSnowballDirectory() / "bin";
  }
  UnreachableError("Invalid workspace directory.");
}

auto CreateWorkspaceDirectories() -> void {
  fs::create_directories(GetSnowballDirectory());

  fs::create_directories(GetWorkspaceDirectory(WorkspaceDirectory::Dependencies));
  fs::create_directories(GetWorkspaceDirectory(WorkspaceDirectory::Build));
  fs::create_directories(GetWorkspaceDirectory(WorkspaceDirectory::Bin));

  fs::create_directories(GetHomeDirectory());
}

auto ReadFile(const fs::Path& path) -> fs::FileStream {
  fs::FileStream file(path);
  if (!file.is_open()) {
    FatalError(utils::Format("Failed to open file: {}", path.string()));
  }
  return file;
}

}; // namespace snowball