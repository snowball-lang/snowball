
#ifndef __SNOWBALL_FRONTEND_AST_MODULE_H__
#define __SNOWBALL_FRONTEND_AST_MODULE_H__

#include <vector>
#include "compiler/frontend/ast/nodes.h"

namespace snowball {
namespace frontend {

class Module {
  ast::TopLevelAst ast;
  NamespacePath path;
public:
  const bool is_main = false;
  std::optional<NamespacePath> parent_crate = std::nullopt;
  Module(ast::TopLevelAst ast, NamespacePath path, bool is_main = false)
    : ast(ast), path(path), is_main(is_main) {}
  ~Module() = default;

  auto& get_ast() { return ast; }
  auto get_path() const { return path; }
  void mutate_ast(ast::Stmt* x) { ast.push_back(x); }
};

}
}

#endif // __SNOWBALL_FRONTEND_AST_MODULE_H_
