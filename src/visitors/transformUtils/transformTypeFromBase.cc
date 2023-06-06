
#include "../Transformer.h"

namespace snowball {
namespace Syntax {

std::shared_ptr<types::Type> Transformer::transformTypeFromBase(
        const std::string& uuid,
        cacheComponents::Types::TypeStore& base, 
        Expression::TypeRef* typeRef) {

    if (auto x = utils::cast<Statement::TypeAlias>(base.type)) {
        assert(false && "TODO: type alias");
    } else if (auto x = utils::cast<Statement::ClassDef>(base.type)) {
        return transformClass(uuid, base, typeRef);
    }

    assert(false);
}

} // namespace Syntax
} // namespace snowball
