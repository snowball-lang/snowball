
#ifndef __SNOWBALL_FRONTEND_AST_NODES_H__
#define __SNOWBALL_FRONTEND_AST_NODES_H__

#include <vector>
#include <memory>

#include "compiler/frontend/location.h"

namespace snowball {
namespace frontend {
namespace ast {

class Node : public LocationHolder {
public:
  Node(const SourceLocation& location) : LocationHolder(location) {}
  virtual ~Node() = default;

  virtual void accept() = 0;
};

class Stmt : public Node {
public:
  Stmt(const SourceLocation& location) : Node(location) {}
  virtual ~Stmt() = default;
};

class Expr : public Node {
public:
  Expr(const SourceLocation& location) : Node(location) {}
  virtual ~Expr() = default;
};

using TopLevelAst = std::vector<Stmt*>;

}
}
}

#define SN_VISIT() virtual void accept() override {} // TODO

#include "compiler/frontend/ast/nodes/stmt.h"
#include "compiler/frontend/ast/nodes/expr.h"

#undef SN_VISIT
#endif // __SNOWBALL_FRONTEND_AST_NODES_H_
