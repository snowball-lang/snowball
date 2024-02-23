
#ifndef __SNOWBALL_FRONTEND_AST_NODES_EXPR_H__
#define __SNOWBALL_FRONTEND_AST_NODES_EXPR_H__

#include "compiler/frontend/ast/nodes/other.h"

namespace snowball {
namespace frontend {
namespace ast {

class Ident final : public Expr, public GenericNode<> {
  std::string name;
public:
  Ident(const SourceLocation& location, const std::string& name, 
    std::optional<GenericNode> generics = std::nullopt)
    : Expr(location), GenericNode(generics), name(name) {}
  ~Ident() = default;

  auto get_name() const { return name; }

  static auto create(const SourceLocation& location, const std::string& name, 
    std::optional<GenericNode> generics = std::nullopt) {
    return new Ident(location, name, generics);
  }

  SN_VISIT()
};

class TypeRef final : public LocationHolder, public GenericNode<TypeRef> {
  Expr* name;
public:
  TypeRef(const SourceLocation& location, Expr* name, 
    std::optional<GenericNode<TypeRef>> generics = std::nullopt)
    : LocationHolder(location), GenericNode(generics), name(name) {}
  ~TypeRef() = default;

  auto get_name() { return name; }

  static auto create(const SourceLocation& location, Expr* name, 
    std::optional<GenericNode<TypeRef>> generics = std::nullopt) {
    return TypeRef(location, name, generics);
  }
};

}
}
}

#endif // __SNOWBALL_FRONTEND_AST_NODES_EXPR_H__
