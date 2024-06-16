
#ifndef __SNOWBALL_FRONTEND_SEMA_CHECK_CTX_H_
#define __SNOWBALL_FRONTEND_SEMA_CHECK_CTX_H_

#include <string>
#include <vector>
#include <variant>

#include "compiler/ctx.h"
#include "compiler/frontend/ast/module.h"
#include "compiler/frontend/ast/nodes.h"
#include "compiler/frontend/ast/visitors.h"
#include "compiler/frontend/sema/universe.h"
#include "compiler/reports/reporter.h"
#include "compiler/utils/utils.h"
#include "compiler/frontend/sema/borrow.h"

#include "compiler/frontend/sema/uuids.h"

namespace snowball {
namespace frontend {
namespace sema {

class TypeCheckItem final {
public:
  enum Kind 
  {
    Func,
    Type,
    Var,
    Module
  };

private:
  Kind kind;
  std::variant<NamespacePath, ast::types::Type*, ast::VarDecl*, std::vector<ast::FnDecl*>> data;

public:
  ~TypeCheckItem() = default;

  // Constructors
  TypeCheckItem(ast::types::Type* type);
  explicit TypeCheckItem(ast::VarDecl* var);
  explicit TypeCheckItem(const std::vector<ast::FnDecl*>& funcs);
  explicit TypeCheckItem(const NamespacePath& module);

  // Accessors
  Kind get_kind() const;
  ast::types::Type* get_type() const;
  ast::VarDecl* get_var() const;
  const std::vector<ast::FnDecl*>& get_funcs() const;
  const NamespacePath& get_module() const;

  bool is_type() const;
  bool is_func() const;
  bool is_var() const;
  bool is_module() const;

  static TypeCheckItem create_type(ast::types::Type* type);
  static TypeCheckItem create_var(ast::VarDecl* var);
  static TypeCheckItem create_fn_decl(const std::vector<ast::FnDecl*>& funcs);
  static TypeCheckItem create_module(const NamespacePath& module);
};

class NameAccumulator final {
  NamespacePath path;
  std::string name = "";

public:
  NameAccumulator()
    : path(NamespacePath::dummy()) {}
  ~NameAccumulator() = default;

  void add(const std::string& part, const std::string& name = "");
  void add(const NamespacePath& path);
  bool is_empty() const { return path.is_empty(); }
  bool is_name() const { return path.size() == 1; } // Just a name, no namespace
  NamespacePath get_path(const std::string& name) const;
  std::string get_name() const { return name; }
  auto get_path() const { return path; }
};

struct MonorphosizedFn final {
  ast::FnDecl* decl;
  std::map<std::string, ast::types::Type*> generics;
};

struct MonorphosizedClass final {
  ast::ClassDecl* decl;
  std::map<std::string, ast::types::Type*> generics;
};

struct TypeCheckerContext final {
  std::vector<NamespacePath> allowed_uuids = ALLOWED_UUIDS;
  Module* current_module = nullptr;
  const ast::FnDecl* current_function = nullptr;
  const ast::ClassDecl* current_class = nullptr;
  std::vector<Scope<TypeCheckItem>> scopes;
  borrow::BorrowChecker borrow_checker;

  ~TypeCheckerContext() = default;
};

} // namespace sema
} // namespace frontend
} // namespace snowball

#endif // __SNOWBALL_FRONTEND_SEMA_CHECK_CTX_H_
