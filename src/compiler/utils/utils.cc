
#include "compiler/utils/utils.h"
#include "compiler/utils/id.h"

#include <vector>
#include <string>
#include <cassert>
#include <algorithm>
#include <cctype>

namespace snowball {
Identified::Identified(uint64_t id) : id(id) {}
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

std::string remove_sub_folders(const std::string& full, const std::string& sub) {
  // Split full path into directories
  std::istringstream fullStream(full);
  std::vector<std::string> fullDirs;
  std::string dir;
  while (std::getline(fullStream, dir, '/')) {
    fullDirs.push_back(dir);
  }  
  // Split subpath into directories
  std::istringstream subStream(sub);
  std::vector<std::string> subDirs;
  while (std::getline(subStream, dir, '/')) {
    subDirs.push_back(dir);
  }
  // Find the position of subpath in full path
  size_t pos = full.find(sub);  
  // If subpath is not found, return the full path
  if (pos == std::string::npos) {
    return full;
  }
  // Find the position of the second occurrence of '/' after the subpath
  size_t secondSlash = full.find('/', pos + sub.length());  
  // If second slash is not found, return the full path
  if (secondSlash == std::string::npos) {
    return full;
  }
  // Extract the part after the second slash
  std::string result = full.substr(secondSlash + 1);
  // Find the position of the next '/' after the second slash
  size_t nextSlash = result.find('/');  
  // If next slash is found, remove everything before it
  if (nextSlash != std::string::npos) {
    result = result.substr(nextSlash + 1);
  }
  // Prepend the directory right before the subpath
  auto result_path = result;
  result_path = result_path.substr(0, result_path.find_first_of('.'));
  return result_path;
}

} // namespace utils
} // namespace snowball
