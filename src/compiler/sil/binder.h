
#ifndef __SNOWBALL_COMPILER_SIL_BINDER_H__
#define __SNOWBALL_COMPILER_SIL_BINDER_H__

#include "compiler/ctx.h"
#include "compiler/sil/insts.h"
#include "compiler/sil/module.h"
#include "compiler/reports/reporter.h"
#include "compiler/frontend/ast/module.h"
#include "compiler/frontend/sema/universe.h"
#include "compiler/frontend/sema/check.h"

namespace snowball {
namespace sil {

using namespace frontend;

/**
 * @brief A class to bind SIL instructions together
 *
 * This class is used to bind SIL instructions together. It is used to bind
 * instructions together to form a function body.
*/
class Binder : public ast::AstVisitor, public Reporter {
  std::vector<frontend::Module>& ast_modules;
  std::vector<Module> sil_modules;
  sil::Module current_module;

  std::map<NamespacePath, ast::types::Type*> types;
  std::vector<ast::types::Type*> constraints;
  std::vector<std::pair<NamespacePath, ast::FnDecl*>> fn_decls;

  Inst* value = nullptr; // The current value of the binder
public:
  Binder(const Ctx& ctx, std::vector<frontend::Module>& modules, sema::Universe<sema::TypeCheckItem>& universe);
  ~Binder() = default;

  void bind();
  Inst* accept(ast::Node* node);

  auto& get_modules() { return sil_modules; }

private:
#define SN_REGISTER_ACCEPT(n) virtual void visit(ast::n* node) override;
#include "compiler/frontend/ast/nodes.def"
#undef SN_REGISTER_ACCEPT
};

}
}

#endif // __SNOWBALL_COMPILER_SIL_BINDER_H__
