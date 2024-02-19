
#ifndef __SNOWBALL_FRONTEND_AST_MODULE_H__
#define __SNOWBALL_FRONTEND_AST_MODULE_H__

#include <vector>
#include "compiler/frontend/ast/nodes.h"

namespace snowball {
namespace frontend {

class Module {
  ast::TopLevelAst ast;
public:
  Module(const ast::TopLevelAst& ast) : ast(ast) {}
  ~Module() = default;

  auto get_ast() const { return ast; }
};

}
}

#endif // __SNOWBALL_FRONTEND_AST_MODULE_H_
