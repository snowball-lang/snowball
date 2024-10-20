
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

auto AsyncComponent::StartAsyncProcess(const clowder::Module& module)
      -> std::future<AsyncComponent::Result> {
  return RunAsync(AsyncComponent(module));
}

auto AsyncComponent::operator()() -> Result {
  // TODO; Implement the frontend process here.
  return Some(Module::Create());
}

}; // namespace snowball::frontend
