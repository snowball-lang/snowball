
#include <future>

#include "clowder/clowder.h"
#include "clowder/src/lib.rs.h"

#include "common/utility/rust.h"
#include "common/utility/async.h"
#include "common/utility/cargo-logger.h"
#include "common/utility/safe-pointer.h"

#include "frontend/driver.h"
#include "frontend/component.h"

using namespace snowball::utils;

namespace snowball::frontend {

auto StartAsyncFrontendProcess(clowder::Package& package, Vector<ModulePtr>& modules) -> bool {
  cargo::DisplayStatus("Building", 
    Format("{} version {}", 
      package.config.name.c_str(),
      package.config.version.c_str()
    )
  );
  Vector<std::future<Opt<ModulePtr>>> futures;
  for (const auto& module : package.modules)
    futures.push_back(AsyncComponent::StartAsyncProcess(module));
  for (auto& future : futures) {
    auto module = future.get();
    if (!module.has_value())
      return Failure;
    modules.push_back(module.value());
  }
  return Success;
}

}; // namespace snowball::frontend
