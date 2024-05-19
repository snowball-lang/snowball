
#ifndef __SNOWBALL_COMPILER_H__
#define __SNOWBALL_COMPILER_H__

#include <string>
#include <vector>

#include "ctx.h"

namespace snowball {

/**
 * @brief The Compiler class is responsible for compiling the source code into a binary file.
 * 
 * The compiler takes care of absolutely everything that is needed to compile the 
 *  source core providing a simple interface to the user.
*/
class Compiler {
  Ctx ctx;
public:
  Compiler(Ctx& ctx);
  ~Compiler() = default;

  /**
   * @brief Compiles the source code into a binary file.
   * 
   * @return true if the compilation was successful, false otherwise.
   */
  bool compile();
  /**
   * @brief Compiles the source code into a binary file.
   * 
   * @param ctx The context of the compiler.
   * @return true if the compilation was successful, false otherwise.
   */
  static bool compile(Ctx& ctx);
private:
  std::string get_package_type_string();
};

}

#endif // __SNOWBALL_COMPILER_H__