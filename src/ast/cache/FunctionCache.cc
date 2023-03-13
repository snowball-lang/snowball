

#include "FunctionCache.h"

#include "../types/DefinedType.h"

namespace snowball {
namespace Syntax {
namespace cacheComponents {

std::shared_ptr<transform::ContextState>& Functions::getFunctionState(id_t id)
    { return functionStates.at(id); }
void Functions::setFunctionState(id_t id, std::shared_ptr<transform::ContextState>& s)
    { functionStates[id] = s; }
void Functions::setFunction(const std::string& name,
                            ptr<Statement::FunctionDef> p_fn,
                            std::shared_ptr<transform::ContextState> state) {
    functions[name].push_back({p_fn, state});
}

std::optional<std::vector<Functions::FunctionStore>>
Functions::getFunction(const std::string name) {
    auto f = functions.find(name);
    if (f != functions.end()) return f->second;

    return std::nullopt;
}

void Functions::setTransformedFunction(const std::string& uuid,
                                       std::shared_ptr<transform::Item> p_fn) {
    if (createdFunctions.count(uuid)) {
        auto x = createdFunctions.at(uuid);
        assert(p_fn->getFunctions().size() == 1);
        x->addFunction(p_fn->getFunctions().at(0));
        return;
    }

    createdFunctions[uuid] = p_fn;
}

std::optional<std::shared_ptr<transform::Item>>
Functions::getTransformedFunction(const std::string uuid) {
    auto f = createdFunctions.find(uuid);
    if (f != createdFunctions.end()) return f->second;

    return std::nullopt;
}

} // namespace cacheComponents
} // namespace Syntax
} // namespace snowball
