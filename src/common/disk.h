
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
SNOWBALL_NO_DISCARD auto GetHomeDirectory() -> fs::Path;

/// @brief Get the workspace directory.
/// @param directory The directory to get.
/// @return The workspace directory.
SNOWBALL_NO_DISCARD 
auto GetWorkspaceDirectory(WorkspaceDirectory directory) -> fs::Path;

/// @brief Get the snowball directory.
/// @return The snowball directory.
SNOWBALL_NO_DISCARD 
auto GetSnowballDirectory() -> fs::Path;

/// @brief Read a file from the disk.
/// @param path The path to the file.
/// @return The file contents.
SNOWBALL_NO_DISCARD
auto ReadFile(const fs::Path& path) -> fs::FileStream;

}; // namespace snowball
