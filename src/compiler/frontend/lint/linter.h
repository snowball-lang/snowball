
#ifndef __SNOWBALL_FRONTEND_LINT_LINTER_H__
#define __SNOWBALL_FRONTEND_LINT_LINTER_H__

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
#include "compiler/frontend/generic/visitor.h"

#include "compiler/llvm_stl.h"

namespace snowball {
namespace frontend {
namespace lint {

class Linter : public GenericVisitor {
public:
  Linter(const Ctx& ctx, std::vector<Module>& modules);
  ~Linter() = default;

  void visit(ast::VarDecl* node) override;
};

}
}
}

#endif // __SNOWBALL_FRONTEND_LINT_LINTER_H__
