

#include "../ir/module/Module.h"
#include "TransformItem.h"

#include <memory>
#include <string>
#include <vector>

#ifndef __SNOWBALL_MACRO_INSTANCE_H_
#define __SNOWBALL_MACRO_INSTANCE_H_

namespace snowball {
namespace Syntax {
namespace transform {

/// @brief Representation of a saved state for the context
struct MacroInstance {
  using StackType = std::map<std::string, std::pair<Node*, Macro::ArguementType>>;

  // The stack of items
  StackType stack = {};
  // The module that the macro is defined in
  std::shared_ptr<ir::Module> module = nullptr;
  // The macro that is being transformed
  Macro* macro = nullptr;

  explicit MacroInstance(Macro* macro, std::shared_ptr<ir::Module> module = nullptr) : macro(macro), module(module) { }
};
} // namespace transform
} // namespace Syntax
} // namespace snowball

#endif // __SNOWBALL_MACRO_INSTANCE_H_
