
#ifndef __SNOWBALL_FRONTEND_AST_NODES_EXPR_H__
#define __SNOWBALL_FRONTEND_AST_NODES_EXPR_H__

#include "compiler/frontend/ast/nodes/other.h"
#include "compiler/utils/id.h"

namespace snowball {
namespace frontend {
namespace ast {

class Ident final : public Expr, public GenericNode<> {
  std::string name;
  uint64_t var_id = 0;
public:
  Ident(const SourceLocation& location, const std::string& name, 
    std::optional<GenericNode> generics = std::nullopt)
    : Expr(location), GenericNode(generics), name(name) {}
  ~Ident() = default;

  auto get_name() const { return name; }
  auto get_var_id() const { return var_id; }
  void set_var_id(uint64_t id) { var_id = id; }

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
