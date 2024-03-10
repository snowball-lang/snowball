
#ifndef __SNOWBALL_COMPILER_UTILS_CLONE_H__
#define __SNOWBALL_COMPILER_UTILS_CLONE_H__

#include <cstdint>

namespace snowball {

template <typename T>
class Cloneable {
public:
  virtual T* clone() const {
    return new T(*static_cast<const T*>(this));
  }
};

}

#endif // __SNOWBALL_COMPILER_UTILS_CLONE_H__

