
#ifndef __SNOWBALL_FRONTEND_AST_NODES_H__
#define __SNOWBALL_FRONTEND_AST_NODES_H__

#include <vector>
#include <memory>

#include "compiler/frontend/location.h"
#include "compiler/frontend/ast/types.h"
#include "compiler/utils/clone.h"

#define SN_DEFAULT_CLONE() \
  Node* clone() const override { return Cloneable<self>::default_clone(this); }

namespace snowball {
namespace frontend {
namespace ast {

class AstVisitor;

class Node : public LocationHolder, public Cloneable<Node> {
  types::Type* type = nullptr;
public:
  Node(const SourceLocation& location) : LocationHolder(location) {}
  virtual ~Node() = default;

  virtual void accept(ast::AstVisitor* v) = 0;

  auto& get_type() { return type; }

  template <typename T>
  [[nodiscard]] auto as() { return dynamic_cast<T*>(this); }
  template <typename T>
  bool is() { return as<T>() != nullptr; }
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

#define SN_VISIT() virtual void accept(ast::AstVisitor* v) override;

#include "compiler/frontend/ast/nodes/stmt.h"
#include "compiler/frontend/ast/nodes/expr.h"
#include "compiler/frontend/ast/nodes/other.h"

#undef SN_VISIT
#endif // __SNOWBALL_FRONTEND_AST_NODES_H_
