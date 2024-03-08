
#ifndef __SNOWBALL_FRONTEND_SEMA_CHECK_H__
#define __SNOWBALL_FRONTEND_SEMA_CHECK_H__

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

// Used for fatal errors
class StopTypeChecking : public std::exception {
public:
  StopTypeChecking() = default;
  ~StopTypeChecking() = default;
};

class TypeCheckItem {
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

class NameAccumulator {
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

class TypeChecker : public ast::AstVisitor, public Reporter {
  Universe<TypeCheckItem> universe;
  std::vector<Module>& modules;
  std::vector<NamespacePath> allowed_uuids;

  const Module* current_module = nullptr;
public:
  TypeChecker(const Ctx& ctx, std::vector<Module>& modules);
  ~TypeChecker() = default;

  void check();
#define SN_REGISTER_ACCEPT(n) virtual void visit(ast::n* node) override;
#include "compiler/frontend/ast/nodes.def"
#undef SN_REGISTER_ACCEPT

  auto& get_universe() { return universe; }
private:
  void register_builtins();

  void err(const LocationHolder& holder, const std::string& message, 
    const Error::Info& info = Error::Info(), Error::Type type = Error::Type::Err, 
    bool fatal = true);

  // --- internal helpers ---

  using GetResult = std::pair<std::optional<TypeCheckItem>, std::string>;

  void generate_global_scope(ast::TopLevelAst& ast);
  NamespacePath get_namespace_path(const std::string& name);
  
  GetResult get_item(ast::Expr* expr, NameAccumulator acc = NameAccumulator());
  GetResult get_item(const NamespacePath& path);
  GetResult get_item(const std::string& name);

  ast::types::Type* get_type(const NamespacePath& path);
  ast::types::Type* get_type(ast::Expr* expr);
  ast::types::Type* get_type(const std::string& name);
  ast::types::Type* get_type(ast::TypeRef& tr);

  bool unify(ast::types::Type*& a, ast::types::Type* b,
    const SourceLocation& holder = SourceLocation::dummy(), bool just_check = false);
  ast::types::UnknownType* get_unknown_type();
  ast::types::ErrorType* get_error_type();
  void define_variable(ast::VarDecl* node, const SourceLocation& loc);
  ast::FnDecl* get_best_match(const std::vector<ast::FnDecl*>& decls, const std::vector<ast::types::Type*>& args, 
    const SourceLocation& loc, bool identified = false);
  bool type_match(ast::types::Type* a, ast::types::Type* b);

  std::optional<std::string> get_did_you_mean(const std::string& name);
};

}
}
}

#endif // __SNOWBALL_FRONTEND_SEMA_CHECK_H_
