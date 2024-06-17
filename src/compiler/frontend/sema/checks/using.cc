


#include "compiler/frontend/ast/nodes.h"
#include "compiler/frontend/sema/check.h"

namespace snowball {
namespace frontend {
namespace sema {

using PathSection = std::pair<NamespacePath, std::optional<std::string>>;

void TypeChecker::do_global_use(ast::Use* use_decl) {
  use_decl->accept(this); // TODO: Maybe cache the result of this?
} 

void TypeChecker::visit(ast::Use* node) {
  std::vector<PathSection> paths;
  // We need to convert things like "std::(map, vec)::collect" to "std::map::collect" and "std::vec::collect"
  for (auto& path : node->get_sections()) {
    std::vector<PathSection> new_paths;
    new_paths.reserve(paths.size() * path.items.size());
    for (auto& [item_path, alias] : path.items) {
      for (auto& [path, parent_alias] : paths) {
        assert(!parent_alias.has_value());
        new_paths.push_back({path + item_path, alias});
      }
      if (paths.empty()) {
        new_paths.push_back({item_path, alias});
      }
    }
    paths = std::move(new_paths);
  }
  for (auto& [path, alias] : paths) {
    auto item = get_item(path, node->get_location());
    assert(alias.has_value());
    if (!item.item.has_value()) {
      err(node->get_location(), F("Could not alias '{}' to '{}'", path.get_path_string(), *alias), Error::Info {
        .highlight = "Element not found",
        .help = "The element you are trying to alias does not exist",
      });
    }
    if (universe.current_scope().get_item(*alias).has_value()) {
      err(node->get_location(), F("Alias '{}' already exists in the current scope", *alias), Error::Info {
        .highlight = "Duplicate alias",
        .help = "Rename the alias to something else",
      });
    }
    universe.add_item(*alias, *item.item);
  }
}

}
}
}
