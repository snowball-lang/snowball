
#include "frontend/driver.h"
#include "clowder/clowder.h"

#include "clowder/src/lib.rs.h"
#include "common/utility/cargo-logger.h"

using namespace snowball::utils;

namespace snowball::frontend {

auto StartAsyncFrontendProcess(clowder::Package& package) -> Module* {
  cargo::DisplayStatus("Building", 
    Format("{} version {}", 
      package.config.name.c_str(),
      package.config.version.c_str()
    )
  );
  return nullptr;
}

}; // namespace snowball::frontend
