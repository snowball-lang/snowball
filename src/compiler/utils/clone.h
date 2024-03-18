
#ifndef __SNOWBALL_COMPILER_UTILS_CLONE_H__
#define __SNOWBALL_COMPILER_UTILS_CLONE_H__

#include <cstdint>

namespace snowball {

template <typename T>
class Cloneable {
public:
  virtual T* clone() const = 0;
  static T* default_clone(const T* self) {
    return new T(*static_cast<const T*>(self));
  }
};

}

#endif // __SNOWBALL_COMPILER_UTILS_CLONE_H__

