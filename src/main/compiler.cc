
#include "reky/reky.h"
#include "main/compiler.h"

#include "common/stl.h"
#include "common/disk.h"
#include "common/utility/logger.h"

using namespace snowball::utils;

namespace snowball {

auto Compiler::Execute() -> bool {
  GetLogger().Debug("Debug verbosity is enabled in the compiler.");
  return ExecutePreCompile();
}

auto Compiler::ExecutePreCompile() -> bool {
  CreateWorkspaceDirectories();
  return ExecuteReky();
}

auto Compiler::ExecuteReky() -> bool {
  // TODO: Return modules to compile.
  return reky::GetRekyManager().Execute();
}

}; // namespace snowball
