
#include "../../ValueVisitor/Visitor.h"
#include "../../ast/syntax/nodes.h"
#include "../../ast/types/Type.h"
#include "../../common.h"
#include "Value.h"

#include <map>
#include <vector>

#ifndef __SNOWBALL_CALL_VALUE_H_
#define __SNOWBALL_CALL_VALUE_H_

namespace snowball {
namespace ir {

/**
 * @brief Representation of a function call in the IR
 */
class Call : public AcceptorExtend<Call, Value> {

    // Function value that's being called
    std::shared_ptr<Value> callee;
    // Arguments passed to the function
    std::vector<std::shared_ptr<Value>> arguments;

  public:
    explicit Call(std::shared_ptr<Value> callee,
                  std::vector<std::shared_ptr<Value>> args = {})
        : callee(callee), arguments(args){};

    /// @return function call arguments
    auto& getArguments() { return arguments; }
    /// @return function call arguments
    auto getCallee() const { return callee; }
    /// @brief Set a new list of arguments to the current call
    void setArguments(std::vector<std::shared_ptr<Value>> v) { arguments = v; }

    // Set a visit handler for the generators
    SN_GENERATOR_VISITS
};

} // namespace ir
} // namespace snowball

#endif // __SNOWBALL_BLOCK_VALUE_H_
