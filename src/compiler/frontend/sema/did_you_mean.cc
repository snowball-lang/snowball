
#include "compiler/frontend/sema/check.h"
#include "compiler/utils/did_you_mean.h"

namespace snowball {
namespace frontend {
namespace sema {

std::optional<std::string> TypeChecker::get_did_you_mean(const std::string& name) {
  std::vector<std::string> names;
  for (auto& scope : universe.get_scopes()) {
    for (auto& [key, value] : scope.get_items()) {
      names.push_back(key);
    }
  }
  return utils::did_you_mean(name, names);
}

}
}
}

