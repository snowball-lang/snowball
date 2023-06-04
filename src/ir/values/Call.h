
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

  public:
    /**
     * @brief A variable used to fix a special occation for
     *  variable mutability. Uninitialized variables should
     *  allow an initial assigment (but just once).
     * @example
     *  let a: i32;
     *  a = 10 // ok
     *  a = 20 // error
     * @note It's a special variable for the OpType::EQ operator.
     */
    bool isInitialization = false;
};

/**
 * @brief Representation of the `new` operator
 */
class ObjectInitialization : public AcceptorExtend<ObjectInitialization, Call> {
    friend Call;

  public:
    explicit ObjectInitialization(std::shared_ptr<Value> callee,
                                  std::vector<std::shared_ptr<Value>> args = {})
        : AcceptorExtend(callee, args) {}

    /// @brief Wether to initialize the object at stack or heap.
    bool initializeAtHeap = true;
};

} // namespace ir
} // namespace snowball

#endif // __SNOWBALL_BLOCK_VALUE_H_
