
#include <algorithm>
#include "compiler/frontend/location.h"

namespace snowball {
namespace frontend {

std::string NamespacePath::get_path_string() const {
  std::string path_str;
  for (size_t i = 0; i < path.size(); ++i) {
    path_str += path[i];
    if (i != path.size() - 1) {
      path_str += "::";
    }
  }
  return path_str;
}

NamespacePath NamespacePath::from_file(const std::filesystem::path& file) {
  std::vector<std::string> path;
  bool add = false;
  for (auto& part : file.parent_path()) {
    if (!add) { // Skip the root path
      add = true;
      continue;
    }
    path.push_back(part.string());
  }
  // Add the file name without extension
  path.push_back(file.stem().string());
  return NamespacePath(path);
}


}
}
