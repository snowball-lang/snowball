
#ifndef __SNOWBALL_FRONTEND_SEMA_CHECK_H__
#define __SNOWBALL_FRONTEND_SEMA_CHECK_H__

#include <string>
#include <vector>

#include "compiler/frontend/ast/module.h"
#include "compiler/frontend/ast/visitors.h"
#include "compiler/frontend/ast/nodes.h"
#include "compiler/frontend/sema/universe.h"
#include "compiler/frontend/sema/ctx.h"
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

class TypeChecker : public ast::AstVisitor, public Reporter {
  Universe<TypeCheckItem> universe;
  std::vector<Module>& modules;
  std::vector<NamespacePath> allowed_uuids;
  std::map<uint64_t, std::vector<MonorphosizedFn>> generic_registry;
  std::map<uint64_t, std::vector<MonorphosizedClass>> generic_class_registry;
  TypeCheckerContext ctx;
  std::unordered_map<uint64_t, TypeCheckerContext> generic_contexts;
public:
  TypeChecker(const Ctx& ctx, std::vector<Module>& modules);
  ~TypeChecker() = default;

  void check();
#define SN_REGISTER_ACCEPT(n) virtual void visit(ast::n* node) override;
#include "compiler/frontend/ast/nodes.def"
#undef SN_REGISTER_ACCEPT

  auto& get_universe() { return universe; }
  auto& get_generic_registry() { return generic_registry; }
private:
  void register_builtins();

  void err(const LocationHolder& holder, const std::string& message, 
    const Error::Info& info = Error::Info(), Error::Type type = Error::Type::Err, 
    bool fatal = true);

  // --- internal helpers ---

  using GetResult = std::pair<std::optional<TypeCheckItem>, std::string>;

  void generate_global_scope(ast::TopLevelAst& ast);
  NamespacePath get_namespace_path(const std::string& name);
  
  GetResult get_item(const ast::Expr* expr, NameAccumulator acc = NameAccumulator());
  GetResult get_item(const NamespacePath& path);
  GetResult get_item(const std::string& name);

  ast::types::Type* get_type(const NamespacePath& path);
  ast::types::Type* get_type(const ast::Expr* expr);
  ast::types::Type* get_type(const std::string& name);
  ast::types::Type* get_type(const ast::TypeRef& tr);

  bool unify(ast::types::Type*& a, ast::types::Type* b,
    const SourceLocation& holder = SourceLocation::dummy(), bool just_check = false);

  ast::types::UnknownType* get_unknown_type();
  ast::types::ErrorType* get_error_type();

  void define_variable(ast::VarDecl* node, const SourceLocation& loc);
  std::optional<std::string> get_did_you_mean(const std::string& name);

  ast::FnDecl* get_best_match(const std::vector<ast::FnDecl*>& decls, const std::vector<ast::types::Type*>& args, 
    const SourceLocation& loc, const std::vector<ast::TypeRef>& generics, bool identified = false);
  ast::FnDecl* deduce_func(ast::FnDecl* node, const std::vector<ast::types::Type*>& args, const SourceLocation& loc, const std::vector<ast::TypeRef>& generics);
  ast::FnDecl* propagate_generic(ast::FnDecl* node, const std::map<std::string, ast::types::Type*>& generics, const SourceLocation& loc);
  ast::FnDecl* monorphosize(ast::FnDecl*& node, const std::map<std::string, ast::types::Type*>& generics, const SourceLocation& loc);
  ast::ClassDecl* monorphosize(ast::ClassDecl*& node, const std::map<std::string, ast::types::Type*>& generics, const SourceLocation& loc);

  ast::types::Type* deduce_type(ast::types::Type* type, const std::vector<ast::types::Type*>& generics, const SourceLocation& loc);

  TypeCheckerContext& get_generic_context(uint64_t id);
  TypeCheckerContext& create_generic_context(uint64_t id);
  void set_generic_context(const TypeCheckerContext& ctx);

  bool type_match(ast::types::Type* a, ast::types::Type* b);

  void do_global_func(ast::FnDecl* fn_decl);
  void do_global_class(ast::ClassDecl* class_decl);
};

}
}
}

#endif // __SNOWBALL_FRONTEND_SEMA_CHECK_H_
