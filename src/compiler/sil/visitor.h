
#ifndef __SNOWBALL_COMPILER_SIL_VISITOR_H__
#define __SNOWBALL_COMPILER_SIL_VISITOR_H__

#include "compiler/ctx.h"
#include "compiler/sil/insts.h"
#include "compiler/sil/module.h"
#include "compiler/reports/reporter.h"
#include "compiler/frontend/ast/module.h"
#include "compiler/frontend/sema/universe.h"
#include "compiler/frontend/sema/check.h"

namespace snowball {
namespace sil {

class SilVisitor {
protected:
  const Ctx& ctx;
public:
  SilVisitor(const Ctx& ctx) : ctx(ctx) {}
  
#define SN_REGISTER_ACCEPT(n) virtual void emit(n* node) = 0;
#include "compiler/sil/insts.def"
#undef SN_REGISTER_ACCEPT

  virtual ~SilVisitor() = default;
};

}
}

#endif // __SNOWBALL_COMPILER_SIL_VISITOR_H__
