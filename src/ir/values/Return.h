
#include "../../ValueVisitor/Visitor.h"
#include "../../ast/syntax/nodes.h"
#include "../../ast/types/Type.h"
#include "../../common.h"
#include "Value.h"

#include <map>
#include <vector>

#ifndef __SNOWBALL_RETURN_VALUE_H_
#define __SNOWBALL_RETURN_VALUE_H_

namespace snowball {
namespace ir {

/**
 * @brief Representation of a return statement
 *  in the IR.
 */
class Return : public AcceptorExtend<Return, Value> {
    // Expression used as value for the return statement
    std::shared_ptr<Value> expr = nullptr;

  public:
    explicit Return(std::shared_ptr<Value> expr) : expr(expr){};

    /**
     * @return value to return
     * @note The value may be std::nullptr because
     *  the user might do `return;` for void functions
     */
    auto getExpr() { return expr; }

    // Set a visit handler for the generators
    SN_GENERATOR_VISITS
};

} // namespace ir
} // namespace snowball

#endif // __SNOWBALL_RETURN_VALUE_H_
