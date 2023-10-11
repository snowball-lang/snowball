
#include "../../ValueVisitor/Visitor.h"
#include "../../ast/syntax/nodes.h"
#include "../../ast/types/Type.h"
#include "../../common.h"
#include "Value.h"

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
  // Identifier we use to fetch the variable
  std::string identifier;
  // Value stored into the current variable
  std::shared_ptr<Value> value;

protected:
  // Whether or not the variable is mutable
  bool _isMutable = false;

  friend Argument;

public:
  // Create a new variable declaration
  VariableDeclaration(const std::string& identifier, std::shared_ptr<Value> value, bool isMutable = false)
      : identifier(identifier), value(value), _isMutable(isMutable){};

  /// @return Variable identifier
  auto getIdentifier() const { return identifier; }
  /// @return respective value stored into the current variable
  auto getValue() const { return value; }
  /// @return true if the variable is mutable
  auto isMutable() { return _isMutable; }

  // Set a visit handler for the generators
  SN_GENERATOR_VISITS
};

} // namespace ir
} // namespace snowball

#endif // __SNOWBALL_VARIABLE_DECL_VALUE_H_
