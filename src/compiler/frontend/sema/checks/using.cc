


#include "compiler/frontend/ast/nodes.h"
#include "compiler/frontend/sema/check.h"

namespace snowball {
namespace frontend {
namespace sema {

void TypeChecker::do_global_use(ast::Use* use_decl) {
  use_decl->accept(this);
  use_decl->set_checked();
} 

void TypeChecker::visit(ast::Use* node) {
  std::vector<NamespacePath> paths;
  // We need to convert things like "std::(map, vec)::collect" to "std::map::collect" and "std::vec::collect"
  for (auto& path : node->get_sections()) {
    std::vector<NamespacePath> new_paths;
    new_paths.reserve(paths.size() * path.items.size());
    for (auto& [item_path, alias] : path.items) {
      sn_assert(!alias, "TODO: Implement aliasing in use statements");
      for (auto& path : paths) {
        new_paths.push_back(path + item_path);
      }
    }
    paths = std::move(new_paths);
  }
  sn_assert(false, "TODO: Implement use statement");
}

}
}
}
