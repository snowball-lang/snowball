

#include "./common.h"
#include "../../DBGSourceInfo.h"

#include <assert.h>
#include <string>
#include <vector>

#ifndef __SNOWBALL_AST_WHERE_CLAUSE_H_
#define __SNOWBALL_AST_WHERE_CLAUSE_H_

namespace snowball {
namespace Syntax {

// Forward declarations
class TypeRef;

/**
 * @brief Represents a "where" clause in a program.
 *
 * The `WhereClause` struct is used to define constraints or conditions
 * in a program. It is typically used in conjunction with templates or
 * generic programming to restrict the types that can be used as arguments.
 *
 * @code rs
 *  fn example<T: Sized + IsPointer>() { ... }
 *                ^^^^^^^^^^^^^^^^^ 2 checks
 * @endcode
 */
struct WhereClause : public Node {
  public:
    using ChecksVectorType = std::vector<TypeRef*>;

  private:
    /**
     * @brief A vector containing the checks that should be executed
     *  for each generic argument.
     */
    ChecksVectorType checks;

  public:
    explicit WhereClause(ChecksVectorType checks) : checks(checks) { }
    explicit WhereClause(TypeRef* check) : checks(ChecksVectorType{checks}) { }

    /// @return The checks to perform
    auto
    getChecks() {
        return checks;
    }
};

} // namespace Syntax
} // namespace snowball

#endif // __SNOWBALL_AST_WHERE_CLAUSE_H_
