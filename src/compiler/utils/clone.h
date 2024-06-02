
#ifndef __SNOWBALL_COMPILER_UTILS_CLONE_H__
#define __SNOWBALL_COMPILER_UTILS_CLONE_H__

#include <cstdint>

namespace snowball {
namespace frontend {
namespace ast {
class Node;
} // namespace ast
} // namespace frontend

template <typename T>
class Cloneable {
public:
  virtual T* clone() const = 0;
  static T* default_clone(const T* self) { 
    auto clone = new T(*static_cast<const T*>(self));
    if constexpr (std::is_base_of_v<frontend::ast::Node, T>) {
      clone->get_type() = nullptr;
    }
    return clone; 
  }
};

} // namespace snowball

#endif // __SNOWBALL_COMPILER_UTILS_CLONE_H__
