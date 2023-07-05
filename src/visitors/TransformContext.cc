
#include "TransformContext.h"

#include "../ast/syntax/nodes.h"
#include "../ast/types/FunctionType.h"
#include "../ir/values/Argument.h"
#include "TransformState.h"

namespace snowball::Syntax {

TransformContext::TransformContext(std::shared_ptr<ir::Module> mod, ir::IRBuilder& builder)
    : AcceptorExtend()
    , module(mod)
    , builder(builder)
    , cache(new Cache())
    , imports(std::make_unique<services::ImportService>()) {
    // Set all of the built in primitive types into the global stack
#define DEFINE_TYPE(t)                                                                             \
    auto raw_##t = std::make_shared<types::t>();                                                   \
    auto _##t = std::make_shared<transform::Item>(raw_##t);                                        \
    addItem(raw_##t->getName(), _##t);

    DEFINE_TYPE(BoolType)
    DEFINE_TYPE(Float64Type)
    DEFINE_TYPE(Float32Type)
    DEFINE_TYPE(Int64Type)
    DEFINE_TYPE(Int32Type)
    DEFINE_TYPE(Int16Type)
    DEFINE_TYPE(Int8Type)
    DEFINE_TYPE(CObjectType)
    DEFINE_TYPE(VoidType)
    DEFINE_TYPE(CharType)

#undef DEFINE_TYPE

    std::vector<std::shared_ptr<types::Type>> overloadTypes = {
            raw_BoolType,  raw_Float64Type, raw_Float32Type, raw_Int64Type,
            raw_Int32Type, raw_Int16Type,   raw_Int8Type,    raw_CharType};

    for (int asPointer = 0; asPointer <= 1; ++asPointer) {

        for (auto ty : overloadTypes) {
            for (auto op : services::OperatorService::operators) {
                for (auto overload : overloadTypes) {
                    auto classType = asPointer ? ty->getPointerTo() : ty;
                    auto overloadType = asPointer ? overload->getPointerTo() : ty;
                    auto typeArgs = {classType, overloadType};
                    auto fn = builder.createFunction(NO_DBGINFO, "#" + op, true, false);
                    auto arg = builder.createArgument(NO_DBGINFO, "other", overloadType);
                    auto type = builder.createFunctionType(typeArgs, ty);
                    fn->setArgs({{"other", arg}});
                    fn->setType(type);
                    fn->setPrivacy(PrivacyStatus::PUBLIC);
                    defineFunction(fn, ty->getName());
                }
            }
        }
    }

    addItem(types::Int32Type::TYPE_ALIAS, _Int32Type);

    auto coreMod = std::make_shared<ir::Module>("Core", imports->CORE_UUID);
    auto coreModItem = std::make_shared<transform::Item>(coreMod);
    addItem("Core", coreModItem);

    std::vector<std::string> coreBuiltins = {"ReturnType", "Sized", "IsNumeric", "IsPointer",
                                             "CastableTo"};

    for (auto builtin : coreBuiltins) {
        auto baseUuid = imports->CORE_UUID + "." + builtin;
        auto transformedType =
                std::make_shared<types::DefinedType>(builtin.c_str(), baseUuid, coreMod);

        auto item = std::make_shared<transform::Item>(transformedType);
        cache->setTransformedType(baseUuid, item);
    }
};

/// @brief get a saved state of the context
std::shared_ptr<transform::ContextState> TransformContext::saveState() {
    auto s = *this->stack;
    s.pop_back();

    return std::make_shared<transform::ContextState>(
            std::make_shared<transform::ContextState::StackType>(s), this->module, currentClass);
}

/// @brief set a state to the current context
void TransformContext::setState(std::shared_ptr<transform::ContextState> s) {
    auto glob = this->stack->back();
    auto st = s->stack;
    st->emplace_back(glob);

    this->stack = st;
    this->module = s->module;
    setCurrentClass(s->currentClass);
}

/// @brief Execute function with saved state
void TransformContext::withState(
        std::shared_ptr<transform::ContextState> s, std::function<void()> cb) {
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
