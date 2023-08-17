#include <string>
#include <vector>

#ifndef __SNOWBALL_OS_DRIVER_H_
#define __SNOWBALL_OS_DRIVER_H_
#include "../../app/cli.h"

namespace snowball {
namespace os {
class Driver {
public:
  /**
   * @brief It executes the given command.
   * @param args The command to execute.
   * @return The exit code of the command.
   */
  static int run(std::vector<std::string> args);
  /**
   * @brief It returns the output filename of the given input filename.
   * @param input The input filename.
   * @param type output type
   * @return The output filename.
   */
  static std::string getOutputFilename(std::string input, app::Options::EmitType type, bool isStatic = false);
};
} // namespace os
} // namespace snowball

#endif // __SNOWBALL_OS_DRIVER_H_