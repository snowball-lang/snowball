
#ifndef __SNOWBALL_FRONTEND_AST_NODES_VISITORS_H__
#define __SNOWBALL_FRONTEND_AST_NODES_VISITORS_H__

#include "compiler/ctx.h"
#include "compiler/frontend/ast/nodes.h"

namespace snowball {
namespace frontend {
namespace ast {

class AstVisitor {
protected:
  const Ctx& vctx;

public:
  AstVisitor(const Ctx& ctx)
    : vctx(ctx) {}

#define SN_REGISTER_ACCEPT(n) virtual void visit(n* node) = 0;
#include "compiler/frontend/ast/nodes.def"
#undef SN_REGISTER_ACCEPT

  virtual ~AstVisitor() = default;
};

} // namespace ast
} // namespace frontend
} // namespace snowball

#endif // __SNOWBALL_FRONTEND_AST_NODES_VISITORS_H_
