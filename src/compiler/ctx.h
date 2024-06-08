
#ifndef __SNOWBALL_CTX_H__
#define __SNOWBALL_CTX_H__

#include <filesystem>

#include "compiler/package.h"
#include "compiler/utils/timers.h"

namespace snowball {

/**
 * @brief The BuildMode enum represents the different build modes of the compiler.
 *
 * The build mode is used to tell the compiler what to do.
 */
enum class BuildMode
{
  Build,
  Run,
  Test
};
/**
 * @brief Emit type as target.
 */
enum class EmitType
{
  Llvm,
  Asm,
  Object,
  Executable,
  Ast,
  Sil,
  LlvmBc
};
/**
 * @brief Optimisation level.
 */
enum class OptLevel
{
  Release,
  Debug,
  ReleaseWithDebug,
  ReleaseFast,
};
/**
 * @brief The OS enum represents the different operating systems.
 */
enum class Target
{
  Windows,
  Linux,
  MacOS,
  Unknown
};
/**
 * @brief Architecture used by the compiler.
 */
enum class Arch
{
  X86_64,
  Arm64,
  Unknown
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
  std::string config_path = "";
  BuildMode build_mode = BuildMode::Build;

  PackageConfig root_package_config = std::nullopt;
  PackageConfig package_config = std::nullopt;
};

} // namespace snowball

#endif // __SNOWBALL_CTX_H__
