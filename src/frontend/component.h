
#include "common/stl.h"
#include "frontend/module.h"
#include "clowder/clowder.h"

#include "common/utility/safe-pointer.h"

#include <future>

namespace snowball {
namespace frontend {

/// @brief A compiler frontend component.
///  This is used to run it asynchronously. Each
///  module can be compiled in parallel, because we don't
///  do any sort of cross-module operations yet.
class AsyncComponent final {
  using Result = Opt<ModulePtr>;

public:
  /// @brief Start a new frontend process.
  auto operator()() -> Result;

  /// @brief Create and run an async frontend process.
  /// @param package The package to compile.
  /// @param modules The modules to compile.
  /// @return Whether the process was successful.
  static auto StartAsyncProcess(const clowder::Module& module)
      -> std::future<Result>;
      
  ~AsyncComponent() = default;
private:
  AsyncComponent(const clowder::Module& module) : mModule(module) {}
  
  clowder::Module mModule; ///< The module to compile..
};

}; // namespace frontend
}; // namespace snowball
