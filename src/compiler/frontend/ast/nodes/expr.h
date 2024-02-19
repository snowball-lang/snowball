
#ifndef __SNOWBALL_FRONTEND_AST_NODES_EXPR_H__
#define __SNOWBALL_FRONTEND_AST_NODES_EXPR_H__

namespace snowball {
namespace frontend {

class ast::TypeRef final : public ast::Expr {
  ast::Expr* name;
  std::vector<ast::TypeRef*> generics;
public:
  TypeRef(const SourceLocation& location, ast::Expr* name, const std::vector<ast::TypeRef*>& generics) 
    : Expr(location), name(name), generics(generics) {}
  ~TypeRef() = default;

  auto get_name() const { return name; }
  auto get_generics() const { return generics; }
};

}
}

#endif // __SNOWBALL_FRONTEND_AST_NODES_EXPR_H__
