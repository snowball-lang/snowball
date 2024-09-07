
#include "common/stl.h"
#include "frontend/module.h"
#include "clowder/clowder.h"

namespace snowball {
namespace frontend {

/// @brief Start a new frontend process.
/// @param package The package to process.
/// @return The module that was created.
SNOWBALL_NO_DISCARD 
auto StartAsyncFrontendProcess(clowder::Package& package) -> Module*;

}; // namespace frontend
}; // namespace snowball
