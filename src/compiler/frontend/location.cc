
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

NamespacePath NamespacePath::from_file(const std::filesystem::path& file, bool without_root) {
  std::vector<std::string> path;
  for (auto& part : file.parent_path()) {
    path.push_back(part.string());
  }
  if (without_root) {
    return NamespacePath(path[1]);
  }
  // Add the file name without extension
  path.push_back(file.stem().string());
  return NamespacePath(path);
}


}
}
