
#include "../../ValueVisitor/Visitor.h"
#include "../../ast/syntax/nodes.h"
#include "../../ast/types/Type.h"
#include "../../common.h"
#include "Value.h"

#include <map>
#include <vector>

#ifndef __SNOWBALL_WHILE_LOOP_VALUE_H_
#define __SNOWBALL_WHILE_LOOP_VALUE_H_

namespace snowball {
namespace ir {

/**
 * @class WhileLoop
 * @brief A class representing a while loop in the abstract syntax tree (AST).
 * @tparam AcceptorExtend<WhileLoop, Value> A template parameter indicating that
 * the `WhileLoop` class is an acceptor that can accept visitors and extends the
 *         `Value` class.
 *
 * This class represents a while loop statement in the AST. It is a subclass of
 * `AcceptorExtend` and extends the `Value` class. The `WhileLoop` class is used
 * to represent loops in the AST, where the loop condition is checked before
 * each iteration of the loop body.
 */
class WhileLoop : public AcceptorExtend<WhileLoop, Value> {

    // Instructions stored inside a block each iteration
    std::shared_ptr<Block> insts;
    // the expression to be evaluated each iteration
    std::shared_ptr<Value> cond;
    // Whether to execute the instruction before or after
    // each iteration
    bool doWhile = false;

  public:
    explicit WhileLoop(std::shared_ptr<Value> cond, std::shared_ptr<Block> insts,
                       bool doWhile = false)
        : cond(cond), insts(insts), doWhile(doWhile){};

    /// @return body block instructions to execute
    //   if the condition is met each iteration
    auto getBlock() const { return insts; }
    /// @return the expression to be evaluated each iteration
    auto getCondition() const { return cond; }
    /// @return If the condition should be checked before or after
    ///  each iteration
    auto isDoWhile() const { return doWhile; }

    // Set a visit handler for the generators
    SN_GENERATOR_VISITS
};

} // namespace ir
} // namespace snowball

#endif // __SNOWBALL_WHILE_LOOP_VALUE_H_
