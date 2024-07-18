
#pragma once

#include "common/stl.h"

namespace snowball {

using OsArguments = Vector<const char*>;

/// @brief The main CLI process.
/// It takes control of the CLI process. It is responsible for
/// parsing the command line arguments, displaying the help message, etc.
bool ParseCommandLine(const OsArguments& args);

} // namespace snowball  
