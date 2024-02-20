
#include "compiler/frontend/location.h"

namespace snowball {
namespace frontend {

std::string NamespacePath::get_path_string() const {
  std::string path_str;
  for (const auto& part : path) {
    path_str += part + "::";
  }
  return path_str;
}

NamespacePath NamespacePath::from_file(const std::filesystem::path& file) {
  std::vector<std::string> path;
  auto parent = file.parent_path();
  while (parent != file.root_path()) {
    path.push_back(parent.filename().string());
    parent = parent.parent_path();
  }
  return NamespacePath(path);
}


}
}
