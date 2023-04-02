
#include "../../ValueVisitor/Visitor.h"
#include "../../ast/syntax/nodes.h"
#include "../../ast/types/Type.h"
#include "../../common.h"
#include "Value.h"

#include <map>
#include <vector>

#ifndef __SNOWBALL_VARIABLE_VALUE_H_
#define __SNOWBALL_VARIABLE_VALUE_H_

namespace snowball {
namespace ir {

/// @brief Representation of a variable access inside the IR.
class Variable : public IdMixin, public AcceptorExtend<Variable, Value> {
    // Identifier we use to fetch the variable
    std::string identifier;
    // Flag indicating whether a variable has been initialized.
    bool initialized = false;
    // If the variable is marked as an argument, we can make certain
    // actions for this specific occasion.
    bool _isArgument = false;
    /// @brief Declaration ID were it's initialized
    id_t declarationID;

  public:
    // Create a new variable declaration
    Variable(const std::string& identifier, bool initialized = false,
             bool isArgument = false)
        : identifier(identifier), _isArgument(isArgument),
          initialized(initialized){};

    /// @return Variable identifier
    auto getIdentifier() const { return identifier; }
    /// @return Wether or not the variable points to an argument
    auto isArgument() { return _isArgument; }
    /// @return ID were it's the variable is initialized
    auto getInitID() { return declarationID; }
    /// @brief Set the ID were the variable is declared
    void setInitID(id_t i) { declarationID = i; }
    /// @brief declare a variable as initialized
    void setInitialized() { initialized = true; }
    /**
     * Flag indicating whether a variable has been initialized.
     *
     * The `initialized` flag is a boolean value that indicates whether a
     * variable has been initialized with a value. When a variable is declared
     * without an initial value, it is considered uninitialized. A variable can
     * be initialized with a value in a number of ways, such as through an
     * assignment statement, in the constructor of a class, or by passing a
     * value as a function argument.
     *
     * Example usage:
     *
     *     let x: i32;          // x is uninitialized
     *     x = 42;         // x is now initialized
     *
     *     class MyClass {
     *     pub:
     *         let myInt: i32;             // myInt is uninitialized
     *
     *         MyClass(i: i32) {
     *             [ The constructor initializes myInt with the value of i ]
     *         }
     *     };
     *
     * @param initialized A boolean value indicating whether the variable has
     * been initialized.
     * @return True if the variable has been initialized, false otherwise.
     */
    auto isInitialized() { return initialized; }

    // Set a visit handler for the generators
    SN_GENERATOR_VISITS
};

} // namespace ir
} // namespace snowball

#endif // __SNOWBALL_VARIABLE_VALUE_H_
