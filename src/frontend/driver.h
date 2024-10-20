
#pragma once

#include "common/stl.h"
#include "frontend/module.h"
#include "clowder/clowder.h"

#include "common/utility/safe-pointer.h"

namespace snowball {
namespace frontend {

/// @brief Start a new frontend process.
/// @param package The package to process.
/// @return The module that was created.
SNOWBALL_NO_DISCARD 
auto StartAsyncFrontendProcess(clowder::Package& package, 
    Vector<ModulePtr>& modules) -> bool;

}; // namespace frontend
}; // namespace snowball
