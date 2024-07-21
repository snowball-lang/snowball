
#pragma once
#include "common/stl.h"

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
  bool mVerbose{false};       // "--verbose"
  bool mDebugVerbose{false};  // "--debug-verbose"
};

extern GlobalContext gContext;
namespace opts {

#define GLOBAL_CONTEXT_GETTER_SWITCH(name, member) \
  bool Is##name() { return gContext.member; }

#define GLOBAL_CONTEXT_SETTER_VALUE(name, member) \
  auto Get##name() -> decltype(gContext.member) { \
    return gContext.member;\
  }

GLOBAL_CONTEXT_GETTER_SWITCH(Verbose, mVerbose)
GLOBAL_CONTEXT_GETTER_SWITCH(DebugVerbose, mDebugVerbose)

GLOBAL_CONTEXT_SETTER_VALUE(Command, mCommand)

#undef GLOBAL_CONTEXT_GETTER_SWITCH
#undef GLOBAL_CONTEXT_SETTER_VALUE

}; // namespace opts
}; // namespace snowball
