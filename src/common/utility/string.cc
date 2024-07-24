
#include "common/stl.h"
#include "common/utility/string.h"

namespace snowball::utils {

auto Split(const String& str, char delim) -> Vector<String> {
  Vector<String> result;
  std::stringstream ss(str);
  String item;
  while (std::getline(ss, item, delim)) {
    result.push_back(item);
  }
  return result;
}

auto Join(const Vector<String>& vec, char delim) -> String {
  String result;
  for (size_t i = 0; i < vec.size(); i++) {
    result += vec[i];
    if (i != vec.size() - 1) {
      result += delim;
    }
  }
  return result;
}

}; // namespace snowball::utils
