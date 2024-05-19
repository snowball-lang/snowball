
#ifndef __SNOWBALL_COMPILER_SIL_VISITOR_H__
#define __SNOWBALL_COMPILER_SIL_VISITOR_H__

#include "compiler/ctx.h"
#include "compiler/sil/insts.h"
#include "compiler/sil/module.h"
#include "compiler/reports/reporter.h"
#include "compiler/frontend/ast/module.h"
#include "compiler/frontend/sema/universe.h"
#include "compiler/frontend/sema/check.h"

#undef F // LLVM Also has this macro and we also have it in "utils.h"
#include "llvm/Support/raw_ostream.h"

#define SNOWBALL_UTILS_REDEFINE_F__
#include "compiler/utils/utils.h"

namespace snowball {
namespace sil {

class SilVisitor {
protected:
  const Ctx& vctx;
public:
  SilVisitor(const Ctx& ctx) : vctx(ctx) {}
  
#define SN_REGISTER_ACCEPT(n) virtual void emit(const n* node) = 0;
#include "compiler/sil/insts.def"
#undef SN_REGISTER_ACCEPT

  virtual ~SilVisitor() = default;
};

class Builder : public SilVisitor {
public:
  Builder(const Ctx& ctx) : SilVisitor(ctx) {}

  virtual void build(std::vector<std::shared_ptr<sil::Module>>& modules) = 0;
  virtual void dump(llvm::raw_ostream& os = llvm::errs()) = 0;
  virtual int emit(std::filesystem::path path) = 0;

  virtual ~Builder() = default;
};

}
}

#endif // __SNOWBALL_COMPILER_SIL_VISITOR_H__
