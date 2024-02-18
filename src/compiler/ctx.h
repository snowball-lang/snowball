
#ifndef __SNOWBALL_CTX_H__
#define __SNOWBALL_CTX_H__

#include <filesystem>

namespace snowball {

/**
 * @brief The BuildMode enum represents the different build modes of the compiler.
 * 
 * The build mode is used to tell the compiler what to do.
 */
enum class BuildMode {
  Build,
  Run,
  Test
};
/**
 * @brief The Ctx class is responsible for managing the context of the compiler.
 * 
 * The context is a set of variables that are used to store information about the
 *  current state of the compiler.
 * @note It just contains flags and other variables to tell the compiler what to do.
 *  it does not contain any sort of environment information.
 */
struct Ctx {
  std::filesystem::path input_file;
  BuildMode build_mode;
};

}

#endif // __SNOWBALL_CTX_H__
