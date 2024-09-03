
#include "clowder/clowder.h"
#include "main/compiler.h"

#include "common/stl.h"
#include "common/disk.h"

#include "common/utility/logger.h"
#include "common/utility/cargo-logger.h"

using namespace snowball::utils;

#define RUN_OR_RETURN(expr) \
  if ((expr) == Failure) return Failure;

namespace snowball {

auto Compiler::Execute() -> bool {
  GetLogger().Debug("Debug verbosity is enabled in the compiler.");
  RUN_OR_RETURN(ExecutePreCompile())
  RUN_OR_RETURN(ExecuteCompile());
  return ExecutePostCompile();
}

auto Compiler::ExecutePreCompile() -> bool {
  CreateWorkspaceDirectories();
  return ExecuteClowder();
}

auto Compiler::ExecuteClowder() -> bool {
  RUN_OR_RETURN(clowder::GetClowderManager().Execute());
  mPackages = clowder::GetClowderManager().GetPackages();
  return Success;
}

auto Compiler::ExecutePostCompile() -> bool {
  return true;
}

auto Compiler::ExecuteCompile() -> bool {
  // cargo::DisplayStatus("Building", "Compiling source code...");
  return true;
}

}; // namespace snowball
