
#include "clowder/clowder.h"
#include "main/compiler.h"

#include "common/stl.h"
#include "common/disk.h"
#include "common/threads.h"

#include "common/utility/logger.h"
#include "common/utility/cargo-logger.h"

#include "frontend/driver.h"

using namespace snowball::utils;

namespace snowball {

auto Compiler::SyncCompile() -> bool {
  GetLogger().Debug("Debug verbosity is enabled in the compiler.");
  RET_FAIL(ExecutePreCompile())
  RET_FAIL(ExecuteCompile());
  return ExecutePostCompile();
}

auto Compiler::Execute() -> bool {
  return Singleton().SyncCompile();
}

auto Compiler::Singleton() -> Compiler& {
  static Compiler instance;
  return instance;
}

auto Compiler::ExecutePreCompile() -> bool {
  CreateWorkspaceDirectories();
  return ExecuteClowder();
}

auto Compiler::ExecuteClowder() -> bool {
  RET_FAIL(clowder::GetClowderManager().Execute());
  mPackages = clowder::GetClowderManager().GetPackages();
  return Success;
}

auto Compiler::ExecutePostCompile() -> bool {
  StopTimer();
  GetLogger().Info(Format("Compilation finished in {}ms", GetTimeElapsed()));
  return Success;
}

auto Compiler::ExecuteFrontendCompiler() -> Vector<frontend::ModulePtr> {
  auto modules = AllocatedVector<frontend::ModulePtr>(mPackages.size());
  ThreadPoolExecutor(mPackages.size(), [&](usize index) {
    auto& package = mPackages[index];
    SNOWBALL_ASSERT_SUCCESS(frontend::StartAsyncFrontendProcess(package, modules),
        "Failed to execute frontend process.");
  });
  return modules;
}

auto Compiler::ExecuteCompile() -> bool {
  StartTimer();
  auto modules = ExecuteFrontendCompiler();
  return Success;
}

}; // namespace snowball
