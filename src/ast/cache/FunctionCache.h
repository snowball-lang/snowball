
#include "../../ir/module/Module.h"
#include "../../ir/values/Func.h"

#include <assert.h>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

#ifndef __SNOWBALL_AST_FUNCTION_CACHE_H_
#define __SNOWBALL_AST_FUNCTION_CACHE_H_

#include "../../visitors/TransformState.h"

namespace snowball {
namespace Syntax {

namespace transform {
class Item;
}

namespace cacheComponents {

/**
 * @brief Cache component for functions
 *
 * Everything about function's polymorfism is stored
 * inside this cache component.
 *
 * Things like overloads, generic functions, etc will
 * be stored here.
 */
class Functions {
public:
  /**
   * @brief Representation of how functions are stored
   *  inside the cache. "State" refers to the transformer
   *  state that manages the current context and scope
   *  it was located at before being added to the cache.
   */
  struct FunctionStore {
    Statement::FunctionDef* function = nullptr;
    std::shared_ptr<transform::ContextState> state;
  };

protected:
  /// @brief A global map containing each function.
  std::map<std::string, std::deque<FunctionStore>> functions;
  /// @brief a list of already transformed functions
  std::map<std::string, std::shared_ptr<transform::Item>> createdFunctions;
  /// @brief A map of states used for generated functions.
  /// @note this can be used for things such as; default arguments
  std::unordered_map<id_t, std::shared_ptr<transform::ContextState>> functionStates;

public:
  /// @brief Set a new function overload
  void setFunction(const std::string& name, Statement::FunctionDef* p_fn,
                   std::shared_ptr<transform::ContextState> state);
  /// @return All function overloads for a function
  std::optional<std::deque<FunctionStore>> getFunction(const std::string name);
  /// @return Get the current state of an already defined
  /// function.
  std::shared_ptr<transform::ContextState>& getFunctionState(id_t id);
  /// @brief defined a new state where the function has been
  /// generated from
  void setFunctionState(id_t id, std::shared_ptr<transform::ContextState>& s);
  /// @brief Set a new transformed function
  /// @c Transformer::addFunction
  void setTransformedFunction(const std::string& uuid, std::shared_ptr<transform::Item> p_fn);
  /// @return get an item of an already transformed function
  std::optional<std::shared_ptr<transform::Item>> getTransformedFunction(const std::string uuid);
  /// Copy a list of functions to a new list for a new type
  void performInheritance(types::DefinedType* ty, types::DefinedType* parent, bool allowConstructor = false);
};

} // namespace cacheComponents
} // namespace Syntax
} // namespace snowball

#endif // __SNOWBALL_AST_FUNCTION_CACHE_H_
