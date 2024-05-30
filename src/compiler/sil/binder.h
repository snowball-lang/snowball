
#ifndef __SNOWBALL_COMPILER_SIL_BINDER_H__
#define __SNOWBALL_COMPILER_SIL_BINDER_H__

#include "compiler/ctx.h"
#include "compiler/frontend/ast/module.h"
#include "compiler/frontend/sema/check.h"
#include "compiler/frontend/sema/universe.h"
#include "compiler/reports/reporter.h"
#include "compiler/sil/insts.h"
#include "compiler/sil/module.h"

#include <unordered_map>

namespace snowball {
namespace sil {

using namespace frontend;

class StopBindingIR final : public std::exception {
public:
  StopBindingIR() = default;
  ~StopBindingIR() = default;
};

struct BinderCtx {
  std::optional<ast::FnDecl*> ast_current_func = std::nullopt;
  std::optional<sil::FuncDecl*> current_func = std::nullopt;
  std::optional<ast::ClassDecl*> ast_current_class = std::nullopt;
};

/**
 * @brief A class to bind SIL instructions together
 *
 * This class is used to bind SIL instructions together. It is used to bind
 * instructions together to form a function body.
 */
class Binder : public ast::AstVisitor, public Reporter {
  std::vector<frontend::Module>& ast_modules;
  std::vector<std::shared_ptr<Module>> sil_modules;
  std::shared_ptr<sil::Module> current_module;

  std::map<NamespacePath, ast::types::Type*> types;
  std::vector<ast::types::Type*> constraints;
  std::vector<std::pair<NamespacePath, ast::FnDecl*>> fn_decls;
  std::unordered_map<uint64_t, sil::Inst*> var_ids;

  bool just_declare = true;

  BinderCtx ctx;
  Inst* value = nullptr; // The current value of the binder
public:
  Binder(const Ctx& ctx, std::vector<frontend::Module>& modules,
         sema::Universe<sema::TypeCheckItem>& universe);
  ~Binder() = default;

  void bind();
  Inst* accept(ast::Node* node);

  auto& get_modules() { return sil_modules; }
  ast::types::Type* get_type(ast::Node* node);
  ast::types::Type* get_type(ast::types::Type* type, const SourceLocation& loc);
  ast::types::Type* check_type(ast::types::Type*& type, const SourceLocation& loc);
  auto& get_insts() { return var_ids; }

  void
  err(const LocationHolder& holder, const std::string& message,
      const Error::Info& info = Error::Info(), Error::Type type = Error::Type::Err,
      bool fatal = false);

private:
#define SN_REGISTER_ACCEPT(n) virtual void visit(ast::n* node) override;
#include "compiler/frontend/ast/nodes.def"
#undef SN_REGISTER_ACCEPT

#include "compiler/sil/optimize.def"
};

} // namespace sil
} // namespace snowball

#endif // __SNOWBALL_COMPILER_SIL_BINDER_H__
