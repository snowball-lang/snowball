
#include "TypeCache.h"

#include "../types/DefinedType.h"

namespace snowball {
namespace Syntax {
namespace cacheComponents {

void
Types::setType(const std::string& uuid,
               Statement::Base* p_ty,
               std::shared_ptr<transform::ContextState>
                       state) {
    assert(utils::cast<Statement::ClassDef>(p_ty) || utils::cast<Statement::TypeAlias>(p_ty));
    types[uuid] = {p_ty, state};
}

void
Types::setTransformedType(const std::string& uuid, std::shared_ptr<transform::Item> p_ty) {
    createdTypes[uuid] = p_ty;
}

std::optional<std::vector<std::shared_ptr<transform::Item>>>
Types::getTransformedType(const std::string& uuidPrefix) {
    std::vector<std::shared_ptr<transform::Item>> typesFound;
    for (auto t : createdTypes) {
        if (t.first.find(uuidPrefix) == 0) typesFound.emplace_back(t.second);
    }

    if (typesFound.size() > 0) return typesFound;

    return std::nullopt;
}

std::optional<Types::TypeStore>
Types::getType(const std::string uuid) {
    auto f = types.find(uuid);
    if (f != types.end()) return f->second;

    return std::nullopt;
}

} // namespace cacheComponents
} // namespace Syntax
} // namespace snowball
