
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
  const Ctx ctx;
public:
  Compiler(const Ctx& ctx);
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
  static bool compile(const Ctx& ctx);
};

}

#endif // __SNOWBALL_COMPILER_H__