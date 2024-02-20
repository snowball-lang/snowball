
#ifndef __SNOWBALL_FRONTEND_AST_NODES_STMT_H__
#define __SNOWBALL_FRONTEND_AST_NODES_STMT_H__

#include <vector>
#include <optional>
#include <string>

#include "compiler/frontend/ast/nodes/other.h"
#include "compiler/frontend/ast/nodes/expr.h" 

namespace snowball {
namespace frontend {
namespace ast {

// --- Forward declarations ---

class TypeRef;

// --- Stmt ---

class Block final : public Stmt {
  std::vector<Node*> stmts;
public:
  Block(const SourceLocation& location, const std::vector<Node*>& stmts) : Stmt(location), stmts(stmts) {}
  ~Block() = default;

  auto get_stmts() const { return stmts; }
  static auto create(const SourceLocation& location, const std::vector<Node*>& stmts) {
    return new Block(location, stmts);
  }

  SN_VISIT()
};

class FnDecl final : public Stmt, public GenericNode<>, public AttributedNode {
public:
  struct Param {
    std::string name;
    TypeRef type;
  };
private:
  std::string name;
  std::vector<Param> params;
  TypeRef return_type;
  Block* body;
public:
  FnDecl(const SourceLocation& location, const std::string& name,   
        const std::vector<Param>& params, TypeRef return_type, Block* body,
        std::optional<GenericNode> generics = std::nullopt, 
        const AttributedNode& attributes = AttributedNode())
    : Stmt(location), GenericNode(generics), AttributedNode(attributes), name(name), params(params), 
      return_type(return_type), body(body) {}
  ~FnDecl() = default;

  auto get_name() const { return name; }
  auto get_params() const { return params; }
  auto get_return_type() const { return return_type; }
  auto get_body() const { return body; }

  static auto create(const SourceLocation& location, const std::string& name, 
      const std::vector<Param>& params, TypeRef return_type, Block* body,
      std::optional<GenericNode> generics = std::nullopt, 
      const AttributedNode& attributes = AttributedNode()) {
    return new FnDecl(location, name, params, return_type, body, generics, attributes);
  }

  SN_VISIT()
};

}
}
}

#endif // __SNOWBALL_FRONTEND_AST_NODES_STMT_H__
