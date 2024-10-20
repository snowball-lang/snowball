
#pragma once

#include "common/stl.h"
#include "common/utility/safe-pointer.h"

namespace snowball {
namespace frontend {

/// @brief Represents a frontend module.
class Module final : public NonCopyable, public SafeCreateable<Module> {
public:
  /// @brief Frontend module types.
  using SafePtr = SafePointer<Module>;
protected:
  friend class SafeCreateable<Module>;
  
  Module() = default;
  ~Module() = default;
};

using ModulePtr = Module::SafePtr;

}; // namespace frontend
}; // namespace snowball  
