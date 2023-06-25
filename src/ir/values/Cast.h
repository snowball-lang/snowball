
#include "../../ValueVisitor/Visitor.h"
#include "../../ast/syntax/nodes.h"
#include "../../ast/types/Type.h"
#include "../../common.h"
#include "Value.h"

#include <map>
#include <vector>

#ifndef __SNOWBALL_CAST_VALUE_H_
#define __SNOWBALL_CAST_VALUE_H_

namespace snowball {
namespace ir {

/**
 * @brief Representation of a cast statement
 *  in the IR.
 */
class Cast : public AcceptorExtend<Cast, Value> {
    /// @brief Expression used as value for the casting
    std::shared_ptr<Value> expr = nullptr;
    /// @brief Type to cast to
    std::shared_ptr<types::Type> castType;

  public:
    explicit Cast(std::shared_ptr<Value> expr, std::shared_ptr<types::Type> castType)
        : expr(expr), castType(castType){};

    /// @return value to cast
    auto getExpr() { return expr; }
    /// @return the result type to cast to
    auto getCastType() { return castType; }

    // Set a visit handler for the generators
    SN_GENERATOR_VISITS
};

} // namespace ir
} // namespace snowball

#endif // __SNOWBALL_CAST_VALUE_H_
