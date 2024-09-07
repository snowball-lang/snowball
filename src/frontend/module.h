
#pragma once

#include "common/stl.h"

namespace snowball {
namespace frontend {

/// @brief Represents a frontend module.
class Module final : public NonCopyable {
public:
  /// @brief Default constructor.
  Module() = default;

  /// @brief Default destructor.
  ~Module() = default;
};

}; // namespace frontend
}; // namespace snowball  
