
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
    //ast::Func* func;
    //ast::Var* var;
  };
public:
  ~TypeCheckItem() = default;
  TypeCheckItem(ast::types::Type* type) : kind(Kind::Type), type(type) {}
  TypeCheckItem(Kind kind, ast::types::Type* type) : kind(kind), type(type) {}

  Kind get_kind() const { return kind; }
  ast::types::Type* get_type() const { return type; }

  bool is_type() const { return kind == Kind::Type; }
  bool is_func() const { return kind == Kind::Func; }
  bool is_var() const { return kind == Kind::Var; }

  static auto create_type(ast::types::Type* type) { 
    return TypeCheckItem(type); 
  }

  static auto create_var(ast::types::Type* type) {
    return TypeCheckItem(Kind::Var, type);
  }
};

class NameAccumulator {
  NamespacePath path;
  std::string name = "";
public:
  NameAccumulator() : path({}) {}
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

  bool unify(ast::types::Type*& a, ast::types::Type* b);
  ast::types::UnknownType* get_unknown_type();
  void define_variable(const std::string& name, ast::types::Type* type);

  std::optional<std::string> get_did_you_mean(const std::string& name);
};

}
}
}

#endif // __SNOWBALL_FRONTEND_SEMA_CHECK_H_
