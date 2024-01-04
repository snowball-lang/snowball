
#include "TransformContext.h"

#include "../ast/syntax/nodes.h"
#include "../ast/types/FunctionType.h"
#include "../ast/types/PointerType.h"
#include "../ir/values/Argument.h"
#include "TransformState.h"

namespace snowball::Syntax {

TransformContext::TransformContext(
  std::shared_ptr<ir::Module> mod, ir::IRBuilder builder, bool testMode, bool benchMode
)
    : AcceptorExtend(), module(mod), testMode(testMode), benchMode(benchMode)
    , isMainModule(true), builder(builder), cache(new Cache())
    , imports(std::make_unique<services::ImportService>(std::filesystem::current_path())) {
  // Set all of the built in primitive types into the global stack
#define DEFINE_TYPE(t)                                                                                                 \
  auto raw_##t = new types::t();                                                                                       \
  auto _##t = std::make_shared<transform::Item>(raw_##t);                                                              \
  addItem(raw_##t->getName(), _##t);

  DEFINE_TYPE(VoidType)

#undef DEFINE_TYPE

  auto coreMod = std::make_shared<ir::Module>("Std", imports->CORE_UUID);
  auto coreModItem = std::make_shared<transform::Item>(coreMod);
  addItem("Std", coreModItem);

  std::vector<std::string> coreBuiltins = {"Sized", "Numeric", "Callable"};

  for (const auto& builtin : coreBuiltins) {
    const auto baseUuid = imports->CORE_UUID + builtin;
    auto transformedType = new types::InterfaceType(builtin, baseUuid, coreMod, {});

    auto item = std::make_shared<transform::Item>(transformedType);
    addItem(builtin, item);
    coreInterfaces.insert({builtin, transformedType});
  }
};

/// @brief get a saved state of the context
std::shared_ptr<transform::ContextState> TransformContext::saveState() {
  auto s = this->stack;
  s.pop_back();

  return std::make_shared<transform::ContextState>(s, this->module, this->uuidStack, this->currentClass);
}

/// @brief set a state to the current context
void TransformContext::setState(std::shared_ptr<transform::ContextState> s) {
  auto glob = this->stack.back();
  auto st = s->stack;
  st.emplace_back(glob);

  this->stack = st;
  this->module = s->module;
  this->uuidStack = s->uuidStack;
  this->builder.setModule(s->module);
  setCurrentClass(s->currentClass);
}

/// @brief Execute function with saved state
void TransformContext::withState(std::shared_ptr<transform::ContextState> s, std::function<void()> cb) {
  auto saved = this->saveState();

  this->setState(s);
  cb();
  this->setState(saved);
}

#if 0
std::pair<std::shared_ptr<transform::Item>, bool> TransformContext::getItem(const std::string name) const {
    auto [i, found] = AcceptorExtend::getItem(name);
    if (found) {
        return {i, found};
    }

    auto fn = cache->getTransformedFunction(name);
    if (fn) {
        return {*fn, true};
    }

    return {nullptr, false};
}
#endif

types::InterfaceType* TransformContext::getBuiltinTypeImpl(const std::string name) {
  auto impl = coreInterfaces.find(name);
  assert(impl != coreInterfaces.end());
  return impl->second;
}

} // namespace snowball::Syntax
