
#ifndef __SNOWBALL_COMPILER_SIL_MODULE_H__
#define __SNOWBALL_COMPILER_SIL_MODULE_H__

#include <optional>
#include <vector>

#include "compiler/frontend/location.h"

namespace snowball {
namespace sil {

class FuncDecl;

class Module {
  std::vector<FuncDecl*> fn_decls;
  frontend::NamespacePath path;
  // TODO: variables
public:
  const bool is_main = false;
  std::optional<frontend::NamespacePath> parent_crate = std::nullopt;
  Module(frontend::NamespacePath path, bool is_main = false)
    : path(path)
    , is_main(is_main) {}
  ~Module() = default;

  void add_fn_decl(FuncDecl* fn_decl) { fn_decls.push_back(fn_decl); }
  auto get_fn_decls() const { return fn_decls; }

  auto get_path() const { return path; }
};

} // namespace sil
} // namespace snowball

#endif // __SNOWBALL_COMPILER_SIL_MODULE_H__
