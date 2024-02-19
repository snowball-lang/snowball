
#ifndef __SNOWBALL_FRONTEND_AST_NODES_EXPR_H__
#define __SNOWBALL_FRONTEND_AST_NODES_EXPR_H__

namespace snowball {
namespace frontend {
namespace ast {

class TypeRef final : public Expr {
  Expr* name;
  std::vector<TypeRef*> generics;
public:
  TypeRef(const SourceLocation& location, Expr* name, const std::vector<TypeRef*>& generics) 
    : Expr(location), name(name), generics(generics) {}
  ~TypeRef() = default;

  auto get_name() const { return name; }
  auto get_generics() const { return generics; }

  static auto create(const SourceLocation& location, Expr* name, const std::vector<TypeRef*>& generics) {
    return new TypeRef(location, name, generics);
  }

  SN_VISIT()
};

}
}
}

#endif // __SNOWBALL_FRONTEND_AST_NODES_EXPR_H__
