#include "../ir/module/Module.h"
#include "TransformItem.h"

#include <memory>
#include <string>
#include <vector>

#ifndef __SNOWBALL_TRANSFORM_STATE_H_
#define __SNOWBALL_TRANSFORM_STATE_H_

namespace snowball {
namespace Syntax {
namespace transform {

/// @brief Representation of a saved state for the context
struct ContextState : std::enable_shared_from_this<ContextState> {
  using StackType = std::list<std::map<std::string, std::shared_ptr<Item>>>;
  StackType stack = {};
  std::shared_ptr<ir::Module> module = nullptr;
  types::Type* currentClass = nullptr;
  std::vector<std::string> uuidStack = {};

  explicit ContextState(
    StackType s,
    std::shared_ptr<ir::Module> module,
    std::vector<std::string> uuidStack,
    types::Type* currentClass = nullptr
  )
    : stack(s), module(module), currentClass(currentClass), uuidStack(uuidStack) { }
};
} // namespace transform
} // namespace Syntax
} // namespace snowball

#endif // __SNOWBALL_TRANSFORM_STATE_H_
