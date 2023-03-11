
#include "TransformContext.h"

#include "TransformState.h"

namespace snowball::Syntax {

TransformContext::TransformContext(std::shared_ptr<ir::Module> mod) {
    module  = mod;
    cache   = new Cache();
    imports = std::make_unique<services::ImportService>();

    // Set all of the built in primitive types into the global stack
    auto raw_boolTy   = std::make_shared<types::BoolType>();
    auto raw_f64Ty    = std::make_shared<types::Float64Type>();
    auto raw_f32Ty    = std::make_shared<types::Float32Type>();
    auto raw_i64Ty    = std::make_shared<types::Int64Type>();
    auto raw_i32Ty    = std::make_shared<types::Int32Type>();
    auto raw_i16Ty    = std::make_shared<types::Int16Type>();
    auto raw_int8Ty   = std::make_shared<types::Int8Type>();
    auto raw_StringTy = std::make_shared<types::StringType>();
    auto raw_COBTy    = std::make_shared<types::CObjectType>();
    auto raw_voidTy   = std::make_shared<types::VoidType>();

    auto boolTy   = std::make_shared<transform::Item>(raw_boolTy);
    auto f64Ty    = std::make_shared<transform::Item>(raw_f64Ty);
    auto f32Ty    = std::make_shared<transform::Item>(raw_f32Ty);
    auto i64Ty    = std::make_shared<transform::Item>(raw_i64Ty);
    auto i32Ty    = std::make_shared<transform::Item>(raw_i32Ty);
    auto i16Ty    = std::make_shared<transform::Item>(raw_i16Ty);
    auto int8Ty   = std::make_shared<transform::Item>(raw_int8Ty);
    auto StringTy = std::make_shared<transform::Item>(raw_StringTy);
    auto cobjTy   = std::make_shared<transform::Item>(raw_COBTy);
    auto VoidTy   = std::make_shared<transform::Item>(raw_voidTy);

    addItem(raw_boolTy->getName(), boolTy);
    addItem(raw_f64Ty->getName(), f64Ty);
    addItem(raw_f32Ty->getName(), f32Ty);
    addItem(raw_i64Ty->getName(), i64Ty);
    addItem(raw_i32Ty->getName(), i32Ty);
    addItem(raw_i16Ty->getName(), i16Ty);
    addItem(raw_int8Ty->getName(), int8Ty);
    addItem(raw_StringTy->getName(), StringTy);
    addItem(raw_voidTy->getName(), VoidTy);
    addItem(raw_COBTy->getName(), cobjTy);

    addItem(types::Int32Type::TYPE_ALIAS, i32Ty);

    addScope();
};

/// @brief get a saved state of the context
transform::ContextState TransformContext::saveState() {
    auto s = this->stack;
    s.pop_back();

    return transform::ContextState{
        .stack = s, .module = this->module, .currentClass = currentClass};
}

/// @brief set a state to the current context
void TransformContext::setState(transform::ContextState s) {
    auto glob = this->stack.back();
    auto st   = s.stack;
    st.emplace_back(glob);

    this->stack        = st;
    this->module       = s.module;
    this->currentClass = s.currentClass;
}

/// @brief Execute function with saved state
void TransformContext::withState(transform::ContextState s,
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
