
#pragma once

#include "common/stl.h"

#if defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__) || defined(__MINGW32__) || defined(WIN32)
#define SNOWBALL_OS_WINDOWS
#elif defined(__APPLE__) || defined(__MACH__)
#define SNOWBALL_OS_MACOS
#elif defined(__linux__) || defined(linux) || defined(__linux)
#define SNOWBALL_OS_LINUX
#else
#define SNOWBALL_OS_UNKNOWN
#endif

#if defined(__x86_64__) || defined(_M_X64) || defined(__amd64) || defined(__amd64__) || defined(__x86_64)
#define SNOWBALL_ARCH_X64
#elif defined(__i386__) || defined(_M_IX86) || defined(i386) || defined(__i386)
#define SNOWBALL_ARCH_X86
#elif defined(__arm__) || defined(__aarch64__)
#define SNOWBALL_ARCH_ARM
#else
#define SNOWBALL_ARCH_UNKNOWN
#endif

namespace snowball {

/// @brief Represents an operating system.
enum class OperatingSystem {
  Windows, MacOS, Linux, Unknown,
};

/// @brief Represents an architecture.
enum class Architecture {
  X86, X64, ARM, Unknown,
};

/// @brief Represents a target. 
/// A target is a combination of an operating system and an architecture,
/// along with other properties. This is used to generate code for a specific
/// target.
class Target final {
public:
  /// @brief Construct a new target.
  /// @param os The operating system.
  /// @param arch The architecture.
  Target(OperatingSystem os, Architecture arch) : mOS(os), mArch(arch) {}

  /// @brief Get the operating system.
  /// @return The operating system.
  SNOWBALL_NO_DISCARD inline auto GetOS() const -> OperatingSystem { return mOS; }

  /// @brief Get the architecture.
  /// @return The architecture.
  SNOWBALL_NO_DISCARD inline auto GetArch() const -> Architecture { return mArch; }

  /// @brief Get the target triple.
  /// @return The target triple.
  SNOWBALL_NO_DISCARD auto GetTriple() const -> String;

  /// @brief Get the target name.
  /// @return The target name.
  SNOWBALL_NO_DISCARD auto GetName() const -> String;

  /// @brief Get the target architecture name.
  /// @return The target architecture name.
  SNOWBALL_NO_DISCARD auto GetArchName() const -> String;

  /// @brief Get the target operating system name.
  /// @return The target operating system name.
  SNOWBALL_NO_DISCARD auto GetOSName() const -> String;

  /// @brief Get the target architecture bit width.
  /// @return The target architecture bit width.
  SNOWBALL_NO_DISCARD auto GetArchBitWidth() const -> u8;

  /// @brief Get the target operating system bit width.
  /// @return The target operating system bit width.
  SNOWBALL_NO_DISCARD auto GetOSBitWidth() const -> u8;

  /// @brief Check if the target is the host target.
  /// @return Whether the target is the host target.
  auto IsHost() const -> bool;

  /// @brief Compare two targets.
  /// @param other The other target.
  /// @return Whether the targets are equal.
  auto operator==(const Target& other) const -> bool {
    return mOS == other.mOS && mArch == other.mArch;
  }

  /// @brief Get the host target.
  /// @return The host target.
  static auto GetHost() -> Target;

  /// @brief Parse a target from a string.
  /// @param target The target string.
  /// @return The parsed target.
  static auto Parse(const String& target) -> Target;
private:
  OperatingSystem mOS;
  Architecture mArch;
};

#ifdef TARGET_FOR_GLOBAL
/// @brief Set the global target to the global context.
/// @return Whether the target was set.
/// @note this should only be called once.
auto SetGlobalTarget() -> bool;
#endif

// Group: fmt utils
auto SnowballFormat(const Target& target) -> String;

}; // namespace snowball
