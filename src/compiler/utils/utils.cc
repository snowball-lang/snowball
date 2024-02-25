
#include "compiler/utils/utils.h"
#include "compiler/utils/id.h"

#include <vector>
#include <string>

namespace snowball {
uint64_t Identified::next_id = 0;

namespace utils {

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

}
}
