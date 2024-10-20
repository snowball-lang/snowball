
#include "common/stl.h"
#include "common/globals.h"
#include "common/target.h"
#include "common/error.h"

#include "common/utility/format.h"
#include "common/utility/string.h"
#include "common/utility/logger.h"

using namespace snowball::utils;

namespace snowball {

auto Target::GetTriple() const -> String {
  return Format("{}-{}", GetOSName(), GetArchName());
}

auto Target::GetName() const -> String {
  return Format("{} ({}) {}", GetTriple(), GetArchBitWidth(),
    IsHost() ? "(host)" : "");
}

auto Target::GetArchName() const -> String {
  switch (mArch) {
    case Architecture::X86: return "x86";
    case Architecture::X64: return "x64";
    case Architecture::ARM: return "arm";
    default: return "unknown";
  }
}

auto Target::GetOSName() const -> String {
  switch (mOS) {
    case OperatingSystem::Windows: return "windows";
    case OperatingSystem::MacOS: return "macos";
    case OperatingSystem::Linux: return "linux";
    default: return "unknown";
  }
}

auto Target::GetArchBitWidth() const -> u8 {
  switch (mArch) {
    case Architecture::X86: return 32;
    case Architecture::X64: return 64;
    case Architecture::ARM: return 32;
    default: return 0;
  }
}

auto Target::GetOSBitWidth() const -> u8 {
  switch (mOS) {
    case OperatingSystem::Windows: return 64;
    case OperatingSystem::MacOS: return 64;
    case OperatingSystem::Linux: return 64;
    default: return 0;
  }
}

auto Target::IsHost() const -> bool {
  return *this == GetHost();
}

auto Target::GetHost() -> Target {
  static Opt<Target> host = None;
  if (!host.has_value()) {
    host = Target(
#ifdef SNOWBALL_OS_WINDOWS
    OperatingSystem::Windows,
#elif defined(SNOWBALL_OS_MACOS)
    OperatingSystem::MacOS,
#elif defined(SNOWBALL_OS_LINUX)
    OperatingSystem::Linux,
#else
    OperatingSystem::Unknown,
#endif
#ifdef SNOWBALL_ARCH_X64
    Architecture::X64
#elif defined(SNOWBALL_ARCH_X86)
    Architecture::X86 
#elif defined(SNOWBALL_ARCH_ARM)  
    Architecture::ARM
#else
    Architecture::Unknown
#endif
    );
  }
  return host.value();
}

auto SnowballFormat(const Target& target) -> String {
  return target.GetTriple();
}

auto Target::Parse(const String& target) -> Target {
  auto parts = Split(target, '-');
  if (parts.size() != 2)
    FatalError(Format("Invalid target triple '{}'. The target triple must be in the format 'os-arch'."
      "\nFor example, your host target triple is '{}'.", target, GetHost().GetTriple()));
  OperatingSystem os;
  Architecture arch;
#define OPERATING_SYSTEM_SWITCH(name, value) \
  if (parts[0] == name) os = OperatingSystem::value;
     OPERATING_SYSTEM_SWITCH("windows",Windows)
else OPERATING_SYSTEM_SWITCH("macos",  MacOS)
else OPERATING_SYSTEM_SWITCH("darwin", MacOS)
else OPERATING_SYSTEM_SWITCH("linux",  Linux)
else FatalError(Format("Expected a valid operating system from the tripple, recieved {}", parts[0]));
#undef OPERATING_SYSTEM_SWITCH
#define ARCHITECTURE_SWITCH(name, value) \
  if (parts[1] == name) arch = Architecture::value;
     ARCHITECTURE_SWITCH("x86", X86)
else ARCHITECTURE_SWITCH("x64", X64)
else ARCHITECTURE_SWITCH("arm", ARM)
else FatalError(Format("Expected a valid architecture from the tripple, recieved {}", parts[1]));
#undef ARCHITECTURE_SWITCH
  return Target(os, arch);
}

auto SetGlobalTarget() -> bool {
  auto target = gContext.mTargetTriple;
  gContext.mTarget = target.empty() 
    ? Target::GetHost() 
    : Target::Parse(target);
  GetLogger().Debug(Format("Set target to '{}'", gContext.mTarget.GetTriple()));
  return Success;
}

} // namespace snowball