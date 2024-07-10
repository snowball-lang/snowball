
#ifndef __SNOWBALL_FRONTEND_SEMA_CHECK_CONTAINER_H_
#define __SNOWBALL_FRONTEND_SEMA_CHECK_CONTAINER_H_

#include <string>
#include <vector>
#include <variant>

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
#include "compiler/frontend/sema/uuids.h"

namespace snowball {
namespace frontend {
namespace sema {

class TypeChecker;
class TypeCheckerBase;

class ExternalDeclarationTracker {
protected:
  // A vector used to keep track of extenral "unmangled" names
  std::vector<std::string> external_declared;
  bool has_entry_declared = false;

  friend class TypeChecker;
  friend class TypeCheckerBase;
};

class GenericRegistriesBase {
protected:
  llvm::DenseMap<uint64_t, std::vector<MonorphosizedFn>> generic_registry;
  llvm::DenseMap<uint64_t, std::vector<MonorphosizedClass>> generic_class_registry;

  llvm::DenseMap<uint64_t, TypeCheckerContext> generic_contexts;

  friend class TypeChecker;
  friend class TypeCheckerBase;
};

class TypeCheckerBase : public ExternalDeclarationTracker, public GenericRegistriesBase {
protected:
  TypeCheckerBase(std::vector<Module>& modules) : modules(modules) {}

  Universe<TypeCheckItem> universe;
  std::vector<Module>& modules;
  TypeCheckerContext ctx;
  GenericInferContext infer_ctx;

  friend class TypeChecker;
public:  
  auto& get_universe() { return universe; }
};

} // namespace sema
} // namespace frontend
} // namespace snowball

#endif // __SNOWBALL_FRONTEND_SEMA_CHECK_CONTAINER_H_
