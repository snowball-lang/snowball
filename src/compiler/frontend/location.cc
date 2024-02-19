
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

}
}
