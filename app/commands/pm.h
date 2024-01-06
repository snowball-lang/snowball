

#include "cli.h"
#include "utils/logger.h"

#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>

#ifndef __SNOWBALL_EXEC_UTILS_CMD_H_
#define __SNOWBALL_EXEC_UTILS_CMD_H_

namespace snowball {
namespace app {
namespace commands {

int clean() {
  Logger::message("Cleaning", "Removing up build files");
  if (fs::exists(".sn")) fs::remove_all(".sn");

  return 0;
}

} // namespace commands
} // namespace app
} // namespace snowball

#endif // __SNOWBALL_EXEC_INIT_CMD_H_

