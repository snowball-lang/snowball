
#ifndef __SNOWBALL_COMPILER_UTILS_HASH_H__
#define __SNOWBALL_COMPILER_UTILS_HASH_H__

namespace snowball {
namespace utils {
namespace hash {

const char XOR_KEY = 0x5A;
const std::string CHAR_SET = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
const int CHAR_SET_SIZE = CHAR_SET.size();
const int MIN_LENGTH = 45;

// Function to hash (encode) the string ensuring alphanumeric characters
static std::string hashString(const std::string &input) {
  std::string hashed;
  for (char c : input) {
    char newChar = CHAR_SET[(c ^ XOR_KEY) % CHAR_SET_SIZE];
    hashed.push_back(newChar);
  }  
  // Add consistent padding to ensure the minimum length
  while (hashed.size() < MIN_LENGTH) {
    hashed.push_back(CHAR_SET[hashed.size() % CHAR_SET_SIZE]);
  }
  return hashed;
}

}
}
}

#endif // __SNOWBALL_COMPILER_UTILS_HASH_H__
