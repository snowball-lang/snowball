
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
  Module(ast::TopLevelAst ast, NamespacePath path) 
    : ast(ast), path(path) {}
  ~Module() = default;

  auto& get_ast() { return ast; }
  auto get_path() const { return path; }
};

}
}

#endif // __SNOWBALL_FRONTEND_AST_MODULE_H_
