
#ifndef __SNOWBALL_FRONTEND_AST_NODES_STMT_H__
#define __SNOWBALL_FRONTEND_AST_NODES_STMT_H__

namespace snowball {
namespace frontend {

class ast::Block final : public ast::Stmt {
  std::vector<ast::Node*> stmts;
public:
  Block(const SourceLocation& location, const std::vector<ast::Node*>& stmts) : Stmt(location), stmts(stmts) {}
  ~Block() = default;

  auto get_stmts() const { return stmts; }
};

class ast::FnDecl final : public ast::Stmt {
public:
  struct Param {
    std::string name;
    ast::TypeRef* type;
  };
private:
  std::string name;
  std::vector<Param> params;
  ast::TypeRef* return_type;
  ast::Block* body;
public:
  FnDecl(const SourceLocation& location, const std::string& name, const std::vector<Param>& params, ast::TypeRef* return_type, ast::Block* body) 
    : Stmt(location), name(name), params(params), return_type(return_type), body(body) {}
  ~FnDecl() = default;

  auto get_name() const { return name; }
  auto get_params() const { return params; }
  auto get_return_type() const { return return_type; }
  auto get_body() const { return body; }
};

}
}

#endif // __SNOWBALL_FRONTEND_AST_NODES_STMT_H__
