
#ifndef __SNOWBALL_COMPILER_SIL_MODULE_H__
#define __SNOWBALL_COMPILER_SIL_MODULE_H__

#include <vector>
#include "compiler/sil/insts.h"
#include "compiler/sil/binder.h"

namespace snowball {
namespace sil {

class Module {
  std::vector<FuncDecl*> fn_decls;
  NamespacePath path;
  // TODO: variables
public:
  Module(NamespacePath path) : path(path) {}
  ~Module() = default;

  void add_fn_decl(FuncDecl* fn_decl) { fn_decls.push_back(fn_decl); }
  auto get_fn_decls() const { return fn_decls; }

  auto get_path() const { return path; }
};

}
}

#endif // __SNOWBALL_COMPILER_SIL_MODULE_H__
