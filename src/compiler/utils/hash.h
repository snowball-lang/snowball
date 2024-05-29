
#include <blake3.h>

#ifndef __SNOWBALL_COMPILER_UTILS_HASH_H__
#define __SNOWBALL_COMPILER_UTILS_HASH_H__

namespace snowball {
namespace utils {
namespace hash {

#define SNOWBALL_HASH_LEN 64

static const std::string hashString(const std::string& str) {
  blake3_hasher hasher;
  blake3_hasher_init(&hasher);
  size_t len = str.length();
  blake3_hasher_update(&hasher, str.c_str(), len);
  uint8_t hash[SNOWBALL_HASH_LEN];
  blake3_hasher_finalize(&hasher, hash, SNOWBALL_HASH_LEN);
  char hash_str[SNOWBALL_HASH_LEN];
  for (size_t i = 0; i < SNOWBALL_HASH_LEN; i += 1) {
    sprintf(hash_str + i, "%02x", hash[i]);
  }
  return hash_str;
}

} // namespace hash
} // namespace utils
} // namespace snowball

#endif // __SNOWBALL_COMPILER_UTILS_HASH_H__
