
#include "../../ValueVisitor/Visitor.h"
#include "../../ast/syntax/nodes.h"
#include "../../ast/types/Type.h"
#include "../../common.h"
#include "Value.h"
#include "Variable.h"

#include <map>
#include <vector>

#ifndef __SNOWBALL_VARIABLE_DECL_VALUE_H_
#define __SNOWBALL_VARIABLE_DECL_VALUE_H_

namespace snowball {
namespace ir {
class Argument;

/// @brief Representation of a variable declaration in the IR
/// Variable declarations can be then used as a way to store values
/// and access them when needed.
class VariableDeclaration : public IdMixin, public AcceptorExtend<Variable, Value> {
  // Variable we are declaring
  std::shared_ptr<ir::Variable> variable;
  // Value stored into the current variable
  std::shared_ptr<Value> value;

protected:
  friend Argument;

public:
  // Create a new variable declaration
  VariableDeclaration(std::shared_ptr<ir::Variable> variable, std::shared_ptr<Value> value)
      : variable(variable), value(value) {};

  /// @return Variable value
  auto& getVariable() const { return variable; }
  /// @return Variable identifier
  std::string getIdentifier() const { return variable->getIdentifier(); }
  /// @return respective value stored into the current variable
  auto getValue() const { return value; }

  // Set a visit handler for the generators
  SN_GENERATOR_VISITS
};

} // namespace ir
} // namespace snowball

#endif // __SNOWBALL_VARIABLE_DECL_VALUE_H_
