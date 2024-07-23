
#pragma once

#include "common/stl.h"
#include "common/error.h"

namespace snowball {
namespace app {

using CommandArgs = Vector<const_ptr_t>;

/// @brief It parses the command line arguments and populates
///  the global context with the appropriate flags.
auto ParseCommandArgs(const CommandArgs& args, const String& command) -> bool;

}; // namespace app
}; // namespace snowball
