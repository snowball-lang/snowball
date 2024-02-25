

#ifndef __SNOWBALL_COMPILER_UTILS_ID_H__
#define __SNOWBALL_COMPILER_UTILS_ID_H__

#include <cstdint>

namespace snowball {

class Identified {
  static uint64_t next_id;
  uint64_t id;
public:
  Identified() : id(next_id++) {}
  auto get_id() const { return id; }
};

}

#endif // __SNOWBALL_COMPILER_UTILS_ID_H__

