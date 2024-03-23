
#ifndef __SNOWBALL_FRONTEND_SEMA_CHECK_CTX_H_
#define __SNOWBALL_FRONTEND_SEMA_CHECK_CTX_H_

#include <string>
#include <vector>

#include "compiler/frontend/ast/module.h"
#include "compiler/frontend/ast/visitors.h"
#include "compiler/frontend/ast/nodes.h"
#include "compiler/frontend/sema/universe.h"
#include "compiler/reports/reporter.h"
#include "compiler/utils/utils.h"
#include "compiler/ctx.h"

namespace snowball {
namespace frontend {
namespace sema {

class TypeCheckItem final {
public:
  enum Kind { Func, Type, Var };
private:
  Kind kind;
  union {
    // TODO:
    ast::types::Type* type;
    ast::VarDecl* var;
  };
  std::vector<ast::FnDecl*> funcs;
public:
  ~TypeCheckItem() = default;
  TypeCheckItem(ast::types::Type* type) : kind(Kind::Type), type(type) {}
  TypeCheckItem(ast::VarDecl* var) : kind(Kind::Var), var(var) {}
  TypeCheckItem(std::vector<ast::FnDecl*>& funcs) : kind(Kind::Func), funcs(funcs) {}

  auto get_kind() const { return kind; }
  auto get_type() const { assert(is_type()); return type; }
  auto get_var() const { assert(is_var()); return var; }
  auto get_funcs() const { assert(is_func()); return funcs; }

  bool is_type() const { return kind == Kind::Type; }
  bool is_func() const { return kind == Kind::Func; }
  bool is_var() const { return kind == Kind::Var; }

  static auto create_type(ast::types::Type* type) { 
    return TypeCheckItem(type); 
  }

  static auto create_var(ast::VarDecl* var) {
    return TypeCheckItem(var);
  }

  static auto create_fn_decl(std::vector<ast::FnDecl*> funcs) {
    return TypeCheckItem(funcs);
  }
};

class NameAccumulator final {
  NamespacePath path;
  std::string name = "";
public:
  NameAccumulator() : path(NamespacePath::dummy()) {}
  ~NameAccumulator() = default;

  void add(const std::string& part, const std::string& name = "");
  bool is_empty() const { return path.is_empty(); }
  bool is_name() const { return path.size() == 1; } // Just a name, no namespace
  NamespacePath get_path(const std::string& name) const;
  std::string get_name() const { return name; }
};

struct MonorphosizedFn final {
  ast::FnDecl* decl;
  std::map<std::string, ast::types::Type*> generics;
};

struct TypeCheckerContext final {
  std::vector<NamespacePath> allowed_uuids;
  Module* current_module = nullptr;
  const ast::FnDecl* current_function = nullptr;
  std::vector<Scope<TypeCheckItem>> scopes;

  ~TypeCheckerContext() = default;
};

}
}
}

#endif // __SNOWBALL_FRONTEND_SEMA_CHECK_CTX_H_
