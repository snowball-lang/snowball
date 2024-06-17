
#ifndef __SNOWBALL_FRONTEND_AST_MODULE_H__
#define __SNOWBALL_FRONTEND_AST_MODULE_H__

#include "compiler/frontend/ast/nodes.h"
#include <vector>

namespace snowball {
namespace frontend {

class Module {
  ast::TopLevelAst ast;
  NamespacePath path;
  bool generated = false;

public:
  const bool is_main = false;
  std::optional<NamespacePath> parent_crate = std::nullopt;
  Module(ast::TopLevelAst ast, NamespacePath path, bool is_main = false)
    : ast(ast), path(path), is_main(is_main) {}
  ~Module() = default;

  auto& get_ast() { return ast; }
  auto& get_path() { return path; }
  void mutate_ast(ast::Stmt* x) { ast.push_back(x); }

  void set_generated(bool generated) { this->generated = generated; }
  bool is_generated() const { return generated; }
};

} // namespace frontend
} // namespace snowball

#endif // __SNOWBALL_FRONTEND_AST_MODULE_H_
