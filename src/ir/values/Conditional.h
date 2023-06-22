
#include "../../ValueVisitor/Visitor.h"
#include "../../ast/syntax/nodes.h"
#include "../../ast/types/Type.h"
#include "../../common.h"
#include "Value.h"

#include <map>
#include <vector>

#ifndef __SNOWBALL_CONDITIONAL_VALUE_H_
#define __SNOWBALL_CONDITIONAL_VALUE_H_

namespace snowball {
namespace ir {

/**
 * @brief Representation of a conditional block or "if statement" in the
 * IR. This contains instructions that are executed inside of it if a
 * condition is met, if not, the "else" statement is executed if it
 * exists.
 */
class Conditional : public AcceptorExtend<Func, Value> {
    // Instructions stored inside a block
    std::shared_ptr<Block> insts;
    // the expression to be evaluated
    std::shared_ptr<Value> cond;
    // The "else" statement block if the condition is false
    std::shared_ptr<Block> elseBlock;

  public:
    explicit Conditional(std::shared_ptr<Value> cond,
                         std::shared_ptr<Block>
                                 insts,
                         std::shared_ptr<Block> elseBlock = nullptr)
        : cond(cond), insts(insts), elseBlock(elseBlock){};

    /// @return body block instructions to execute
    //   if the condition is met
    auto
    getBlock() {
        return insts;
    }
    /// @return the expression to be evaluated
    auto
    getCondition() {
        return cond;
    }

    /// @return Get "else" statement
    auto
    getElse() {
        return elseBlock;
    }

    // Set a visit handler for the generators
    SN_GENERATOR_VISITS
};

} // namespace ir
} // namespace snowball

#endif // __SNOWBALL_CONDITIONAL_VALUE_H_