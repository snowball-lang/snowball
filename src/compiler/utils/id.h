

#ifndef __SNOWBALL_COMPILER_UTILS_ID_H__
#define __SNOWBALL_COMPILER_UTILS_ID_H__

#include <cstdint>

namespace snowball {

class Identified {
  static uint64_t next_id;
  uint64_t id;
public:
  Identified();
  Identified(uint64_t id) : id(id) {}
  auto get_id() const { return id; }
  void increment_id() { id = next_id++; } // Use this only if you know what you're doing
};

}

#endif // __SNOWBALL_COMPILER_UTILS_ID_H__

