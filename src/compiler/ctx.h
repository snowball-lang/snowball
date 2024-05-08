
#ifndef __SNOWBALL_CTX_H__
#define __SNOWBALL_CTX_H__

#include <filesystem>
#include "compiler/package.h"

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
 * @brief Emit type as target.
 */
enum class EmitType {
  Llvm, 
  Asm,
  Object,
  Executable,
  Ast,
  Sil
};
/**
 * @brief Optimisation level.
 */
enum class OptLevel {
  None,
  O1,
  O2,
  O3,
  Os,
  Oz  
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
  EmitType emit_type;
  OptLevel opt_level = OptLevel::None;

  PackageConfig package_config = std::nullopt;
};

}

#endif // __SNOWBALL_CTX_H__
