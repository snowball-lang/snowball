
#include "TransformContext.h"

#include "TransformState.h"

namespace snowball::Syntax {

TransformContext::TransformContext(std::shared_ptr<ir::Module> mod)
    : AcceptorExtend() {
    module  = mod;
    cache   = new Cache();
    imports = std::make_unique<services::ImportService>();

    // Set all of the built in primitive types into the global stack
#define DEFINE_TYPE(t)                                                         \
    auto raw_##t = std::make_shared<types::t>();                               \
    auto _##t    = std::make_shared<transform::Item>(raw_##t);                 \
    addItem(raw_##t->getName(), _##t);

    DEFINE_TYPE(BoolType)
    DEFINE_TYPE(Float64Type)
    DEFINE_TYPE(Float32Type)
    DEFINE_TYPE(Int64Type)
    DEFINE_TYPE(Int32Type)
    DEFINE_TYPE(Int16Type)
    DEFINE_TYPE(Int8Type)
    DEFINE_TYPE(StringType)
    DEFINE_TYPE(CObjectType)
    DEFINE_TYPE(VoidType)
    DEFINE_TYPE(CharType)

#undef DEFINE_TYPE

    addItem(types::Int32Type::TYPE_ALIAS, _Int32Type);
};

/// @brief get a saved state of the context
std::shared_ptr<transform::ContextState> TransformContext::saveState() {
    auto s = *this->stack;
    s.pop_back();

    return std::make_shared<transform::ContextState>(
        std::make_shared<transform::ContextState::StackType>(s), this->module,
        currentClass);
}

/// @brief set a state to the current context
void TransformContext::setState(std::shared_ptr<transform::ContextState> s) {
    auto glob = this->stack->back();
    auto st   = s->stack;
    st->emplace_back(glob);

    this->stack  = st;
    this->module = s->module;
    setCurrentClass(s->currentClass);
}

/// @brief Execute function with saved state
void TransformContext::withState(std::shared_ptr<transform::ContextState> s,
                                 std::function<void()> cb) {
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

} // namespace snowball::Syntax
