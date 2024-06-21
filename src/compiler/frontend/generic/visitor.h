

#ifndef __SNOWBALL_FRONTEND_GENERIC_VISITOR_H__
#define __SNOWBALL_FRONTEND_GENERIC_VISITOR_H__

#include <string>
#include <vector>

#include "compiler/ctx.h"
#include "compiler/frontend/ast/module.h"
#include "compiler/frontend/ast/nodes.h"
#include "compiler/frontend/ast/visitors.h"
#include "compiler/frontend/sema/ctx.h"
#include "compiler/frontend/sema/universe.h"
#include "compiler/reports/reporter.h"
#include "compiler/utils/utils.h"
#include "compiler/frontend/sema/borrow.h"

#include "compiler/llvm_stl.h"

namespace snowball {
namespace frontend {

struct GenericVisitorContext {
  std::optional<ast::FnDecl*> current_function;
  std::optional<ast::ClassDecl*> current_class;
};

// Generic visitor that visits all the nodes in the AST
// and it can be used for linting, documentation generation, etc.
class GenericVisitor : public ast::AstVisitor, public Reporter {
  std::vector<Module>& modules;
  GenericVisitorContext ctx;

public:
  GenericVisitor(const Ctx& ctx, std::vector<Module>& modules);
  ~GenericVisitor() = default;

  virtual void visit();

  void
  err(const LocationHolder& holder, const std::string& message,
      const Error::Info& info = Error::Info(), Error::Type type = Error::Type::Err);
  void warn(const LocationHolder& holder, const std::string& message,
            const Error::Info& info = Error::Info());

  bool shoudnt_error() const;

#define SN_REGISTER_ACCEPT(n) virtual void visit(ast::n* node) override;
#include "compiler/frontend/ast/nodes.def"
#undef SN_REGISTER_ACCEPT

};

}
}

#endif // __SNOWBALL_FRONTEND_GENERIC_VISITOR_H__

