
#include "compiler/utils/utils.h"
#include "compiler/utils/id.h"

#include <vector>
#include <string>
#include <cassert>
#include <algorithm>
#include <cctype>

namespace snowball {
uint64_t Identified::next_id = 1;
Identified::Identified() : id(next_id++) { }

namespace utils {

void strip(std::string& str) {
  str.erase(std::remove_if(str.begin(), str.end(), [](unsigned char x) { return std::isspace(x); }), str.end());
}

std::vector<std::string> split(std::string str, const std::string& delimiter) {
  std::vector<std::string> result;
  while (str.size()) {
    int index = str.find(delimiter);
    if (index != (int)std::string::npos) {
      result.push_back(str.substr(0, index));
      str = str.substr(index + delimiter.size());
      if (str.size() == 0) result.push_back(str);
    } else {
      result.push_back(str);
      str = "";
    }
  }
  return result;
}

bool sw(const std::string& str, const std::string& prefix) {
  return str.substr(0, prefix.size()) == prefix;
}

std::string join(const std::vector<std::string>& vec, const std::string& delimiter) {
  std::string result;
  for (size_t i = 0; i < vec.size(); ++i) {
    result += vec[i];
    if (i != vec.size() - 1) {
      result += delimiter;
    }
  }
  return result;
}

} // namespace utils
} // namespace snowball
