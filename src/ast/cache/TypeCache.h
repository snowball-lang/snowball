
#include "../../ir/values/Func.h"

#include <assert.h>
#include <optional>
#include <string>
#include <vector>

#ifndef __SNOWBALL_AST_TYPE_CACHE_H_
#define __SNOWBALL_AST_TYPE_CACHE_H_

#include "../../visitors/TransformItem.h"
#include "../../visitors/TransformState.h"
#include "../types/DefinedType.h"
#include "../types/TypeAlias.h"

namespace snowball {
namespace Syntax {

namespace transform {
class Item;
}

namespace cacheComponents {

/**
 * @brief Cache component for types.
 *
 * Types can have generics, making them unique
 * based on their generics also making my life misserable.
 */
class Types {
  public:
    /**
     * @brief Representation of how functions are stored
     *  inside the cache. "State" refers to the transformer
     *  state that manages the current context and scope
     *  it was located at before being added to the cache.
     */
    struct TypeStore {
        Statement::Base* type = nullptr;
        std::shared_ptr<transform::ContextState> state;
    };

  protected:
    /// @brief A global map containing each class.
    std::map<std::string, TypeStore> types;
    /// @brief a list of already transformed types
    std::map<std::string, std::shared_ptr<transform::Item>> createdTypes;

  public:
    /// @brief A map containing what UUIDs are associated with it's original identifiers
    /// @example Foo -> [Foo:1, Foo:2, ...]
    std::map<std::string, std::vector<std::string>> identifierLookup;

  public:
    /// @brief Set a new type to the cache
    void setType(const std::string& uuid, Statement::Base* p_ty, std::shared_ptr<transform::ContextState> state);
    /// @brief add a new generated class to the cache
    void setTransformedType(const std::string& uuid, std::shared_ptr<transform::Item> p_ty,
                            const std::string overloadedUUID = "");
    /// @brief add a new generated class to the cache
    std::optional<std::vector<std::shared_ptr<transform::Item>>> getTransformedType(const std::string& uuid);
    /// @return All function overloads for a function
    std::optional<TypeStore> getType(const std::string uuid);
};

} // namespace cacheComponents
} // namespace Syntax
} // namespace snowball

#endif // __SNOWBALL_AST_TYPE_CACHE_H_
