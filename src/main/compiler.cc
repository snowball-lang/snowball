
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
  Stop();
  return true;
}

auto Compiler::ExecuteFrontendCompiler() -> Vector<frontend::Module*> {
  auto modules = AllocatedVector<frontend::Module*>(mPackages.size());
  ThreadPoolExecutor(mPackages.size(), [&](usize index) {
    auto& package = mPackages[index];
    auto module = frontend::StartAsyncFrontendProcess(package);
    modules.push_back(module);
  });
  return modules;
}

auto Compiler::ExecuteCompile() -> bool {
  Start();
  // cargo::DisplayStatus("Building", "Compiling source code...");
  auto modules = ExecuteFrontendCompiler();
  return true;
}

}; // namespace snowball
