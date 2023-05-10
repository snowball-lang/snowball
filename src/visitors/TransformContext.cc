
#include "TransformContext.h"

#include "../ast/types/FunctionType.h"
#include "../ir/values/Argument.h"
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

    std::vector<std::shared_ptr<types::Type>> overloadTypes = {
        raw_BoolType,  raw_Float64Type, raw_Float32Type,
        raw_Int64Type, raw_Int32Type,   raw_Int16Type,
        raw_Int8Type,  raw_StringType,  raw_CharType};

    for (auto ty : overloadTypes) {
        for (auto op : services::OperatorService::operators) {
            for (auto overload : overloadTypes) {
                auto fn  = std::make_shared<ir::Func>("#" + op, true, false);
                auto arg = std::make_shared<ir::Argument>("other");
                auto typeArgs = {ty, overload};
                auto type = std::make_shared<types::FunctionType>(typeArgs, ty);

                arg->setType(overload);

                fn->setArgs({{"other", arg}});
                fn->setType(type);
                fn->setPrivacy(/* public */ false);

                /// @see Transformer::defineFunction
                auto name = ty->getName() + "." + fn->getName(true);
                auto item = cache->getTransformedFunction(name);
                if (item) {
                    assert((*item)->isFunc());
                    (*item)->addFunction(fn);
                    continue;
                }

                auto i = std::make_shared<transform::Item>(fn);
                cache->setTransformedFunction(name, i);
            }
        }
    }

    addItem(types::Int32Type::TYPE_ALIAS, _Int32Type);

    auto coreMod     = std::make_shared<ir::Module>("Core", imports->CORE_UUID);
    auto coreModItem = std::make_shared<transform::Item>(coreMod);
    addItem("Core", coreModItem);

    std::vector<std::string> coreBuiltins = {"ReturnType"};

    for (auto builtin : coreBuiltins) {
        auto baseUuid        = imports->CORE_UUID + "." + builtin;
        auto transformedType = std::make_shared<types::DefinedType>(
            builtin.c_str(), baseUuid, coreMod);

        auto item = std::make_shared<transform::Item>(transformedType);
        cache->setTransformedType(baseUuid, item);
    }
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
