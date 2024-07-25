
#pragma once

#include "common/stl.h"
#include "common/utility/assert.h"

namespace snowball {

enum class WorkspaceDirectory : u8 {
  Dependencies, Build,
  Bin,
};

/// @brief Create workspace directories for the project+
///  if they do not exist.
auto CreateWorkspaceDirectories() -> void;

/// @brief Get snowball's home directory.
/// @return The home directory.
[[nodiscard]] auto GetHomeDirectory() -> fs::Path;

/// @brief Get the workspace directory.
/// @param directory The directory to get.
/// @return The workspace directory.
[[nodiscard]] auto GetWorkspaceDirectory(WorkspaceDirectory directory) -> fs::Path;

/// @brief Get the snowball directory.
/// @return The snowball directory.
[[nodiscard]] auto GetSnowballDirectory() -> fs::Path;

}; // namespace snowball
