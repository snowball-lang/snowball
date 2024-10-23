
#pragma once

#include "common/stl.h"
#include "common/target.h"

namespace snowball {

enum class Command {
  Run, Build,
};

/// @brief This is a global context for the compiler.
/// it is thread-safe and can be used around everywhere, it is a singleton.
struct GlobalContext {
  GlobalContext() = default;
  ~GlobalContext() = default;

  GlobalContext(const GlobalContext&) = delete;
  GlobalContext(GlobalContext&&) = delete;
  GlobalContext& operator=(const GlobalContext&) = delete;

  Command mCommand{Command::Run};
  bool    mVerbose{false};       // "--verbose"
  bool    mDebugVerbose{false};  // "--debug-verbose"
  u8      mNumThreads{0};        // "--threads"
  String  mTargetTriple{""};     // "--target"

  // The target triple, will be parsed from the target triple string.
  Target  mTarget{OperatingSystem::Unknown, Architecture::Unknown};
  usize   mErrorCount{0};
};

extern GlobalContext gContext;
namespace opts {

#define GLOBAL_CONTEXT_GETTER_SWITCH(name, member) \
  static bool Is##name() { return gContext.member; }

#define GLOBAL_CONTEXT_GETTER_VALUE(name, member) \
  static auto Get##name() -> decltype(gContext.member) { \
    return gContext.member;\
  }

GLOBAL_CONTEXT_GETTER_SWITCH(Verbose, mVerbose)
GLOBAL_CONTEXT_GETTER_SWITCH(DebugVerbose, mDebugVerbose)

GLOBAL_CONTEXT_GETTER_VALUE(Command, mCommand)
GLOBAL_CONTEXT_GETTER_VALUE(NumThreads, mNumThreads)
GLOBAL_CONTEXT_GETTER_VALUE(TargetTriple, mTargetTriple)
GLOBAL_CONTEXT_GETTER_VALUE(Target, mTarget)
GLOBAL_CONTEXT_GETTER_VALUE(ErrorCount, mErrorCount)

#undef GLOBAL_CONTEXT_GETTER_SWITCH
#undef GLOBAL_CONTEXT_GETTER_VALUE

}; // namespace opts
}; // namespace snowball
