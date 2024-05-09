
#ifndef __SNOWBALL_CLI_H__
#define __SNOWBALL_CLI_H__

#include "compiler/ctx.h"
#include "compiler/package.h"

namespace snowball {
namespace cli {

/**
 * @brief The CLI class is responsible for managing the command line interface of the compiler.
 * 
 * The CLI class is responsible for parsing the command line arguments and
 *  providing a simple interface to the user.
 */
class CLI {
public:
  CLI();
  ~CLI() = default;

  /**
   * @brief Parses the command line arguments.
   * 
   * @param argc The number of arguments.
   * @param argv The arguments.
   * @return true if the parsing was successful, false otherwise.
   */
  Ctx parse(int argc, char** argv);

  /**
   * @brief Gets the package configuration.
   * 
   * @param ctx The context of the compiler.
   * @param path The path to the configuration file.
   */
  static void get_package_config(Ctx& ctx, const std::string& path = "");
private:
  void make_run();
};

}
}

#endif // __SNOWBALL_CLI_H__
