
#ifndef __SNOWBALL_FRONTEND_AST_NODES_VISITORS_H__
#define __SNOWBALL_FRONTEND_AST_NODES_VISITORS_H__

#include "compiler/frontend/ast/nodes.h"
#include "compiler/ctx.h"

namespace snowball {
namespace frontend {
namespace ast {

class AstVisitor {
protected:
  const Ctx& ctx;
public:
  AstVisitor(const Ctx& ctx) : ctx(ctx) {}
  
#define SN_REGISTER_ACCEPT(n) virtual void visit(n* node) = 0;
#include "compiler/frontend/ast/nodes.def"
#undef SN_REGISTER_ACCEPT

  virtual ~AstVisitor() = default;
};

}
}
}

#endif // __SNOWBALL_FRONTEND_AST_NODES_VISITORS_H_
