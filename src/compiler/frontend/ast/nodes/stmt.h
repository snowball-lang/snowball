
#ifndef __SNOWBALL_FRONTEND_AST_NODES_STMT_H__
#define __SNOWBALL_FRONTEND_AST_NODES_STMT_H__

#include <vector>
#include <optional>
#include <string>

#include "compiler/utils/id.h"
#include "compiler/frontend/ast/nodes/other.h"
#include "compiler/frontend/ast/nodes/expr.h" 

namespace snowball {
namespace frontend {
namespace ast {

// --- Forward declarations ---

class TypeRef;
class VarDecl;

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

class FnDecl final : public Stmt, public GenericNode<>, public AttributedNode, public Identified {
public:
private:
  std::string name;
  std::vector<VarDecl*> params;
  TypeRef return_type;
  Block* body;
public:
  FnDecl(const SourceLocation& location, const std::string& name,   
        const std::vector<VarDecl*>& params, TypeRef return_type, Block* body,
        std::optional<GenericNode> generics = std::nullopt, 
        const AttributedNode& attributes = AttributedNode())
    : Stmt(location), GenericNode(generics), AttributedNode(attributes), name(name), params(params), 
      return_type(return_type), body(body) {}
  ~FnDecl() = default;

  auto& get_name() const { return name; }
  auto& get_params() { return params; }
  auto& get_return_type() { return return_type; }
  auto get_body() const { return body; }

  static auto create(const SourceLocation& location, const std::string& name, 
      const std::vector<VarDecl*>& params, TypeRef return_type, Block* body,
      std::optional<GenericNode> generics = std::nullopt, 
      const AttributedNode& attributes = AttributedNode()) {
    return new FnDecl(location, name, params, return_type, body, generics, attributes);
  }

  SN_VISIT()
};

class VarDecl final : public Stmt, public AttributedNode, public Identified {
  std::string name;
  std::optional<TypeRef> type;
  std::optional<Expr*> value;
public:
  VarDecl(const SourceLocation& location, const std::string& name, 
      std::optional<TypeRef> type, std::optional<Expr*> value, 
      const AttributedNode& attributes = AttributedNode())
    : Stmt(location), AttributedNode(attributes), name(name), type(type), value(value) {}
  ~VarDecl() = default;

  auto& get_name() const { return name; }
  auto& get_decl_type() { return type; }
  auto& get_value() { return value; }

  static auto create(const SourceLocation& location, const std::string& name, 
      std::optional<TypeRef> type, std::optional<Expr*> value, 
      const AttributedNode& attributes = AttributedNode()) {
    return new VarDecl(location, name, type, value, attributes);
  }

  SN_VISIT()
};

}
}
}

#endif // __SNOWBALL_FRONTEND_AST_NODES_STMT_H__
