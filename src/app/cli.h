
#ifndef __SNOWBALL_CLI_H__
#define __SNOWBALL_CLI_H__

#include "compiler/ctx.h"
#include "compiler/package.h"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#define SN_WIN
#elif defined(__linux__)
#define SN_LIN
#elif defined(__APPLE__) || defined(__MACH__)
#define SN_MAC
#else
#define SN_UNK
#endif

#if defined(__x86_64__) || defined(_M_X64)
#define SN_X86_64
#elif defined(AARCH64) || defined(__aarch64__)
#define SN_ARM64
#endif

#ifdef NDEBUG
#define SNOWBALL_BUILD_TYPE "release"
#else
#define SNOWBALL_BUILD_TYPE "debug"
#endif

namespace snowball {
namespace cli {

/**
 * @brief The CLI class is responsible for managing the command line interface of the compiler.
 * 
 * The CLI class is responsible for parsing the command line arguments and
 *  providing a simple interface to the user.
 */
class CLI {
  using Args = std::vector<const char*>;
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
  static void make_build(Ctx& ctx, Args& args, bool for_run = false);
  static void make_init(Ctx& ctx, Args& args, bool new_project = false);

  static void parse_args(Args& args);
  static void print_help(Args& args);
 
  static void hide_args();
};

}
}

#endif // __SNOWBALL_CLI_H__
