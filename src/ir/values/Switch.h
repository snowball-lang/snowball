
#include "../../ValueVisitor/Visitor.h"
#include "../../ast/syntax/nodes.h"
#include "../../ast/types/Type.h"
#include "../../common.h"
#include "Value.h"

#include <map>
#include <vector>

#ifndef __SNOWBALL_SWITCH_VALUE_H_
#define __SNOWBALL_SWITCH_VALUE_H_

namespace snowball {
namespace ir {

/**
 * @brief Representation of a switch statement
 * in the IR.
 */
class Switch : public AcceptorExtend<Switch, Value> {
public:
  /// @brief Case for the switch
  struct Case {
    /// @brief Value to compare
    std::vector<std::shared_ptr<VariableDeclaration>> args;
    /// @brief Block to jump to
    std::shared_ptr<Block> block;
    /// @brief Name of the case
    std::string name;
  };
private:
  /// @brief Expression used as value for the switch
  std::shared_ptr<Value> expr = nullptr;
  /// @brief Cases for the switch
  std::vector<Case> cases;
  /// @brief Default case for the switch
  std::shared_ptr<Block> defaultCase = nullptr;

public:
  explicit Switch(std::shared_ptr<Value> expr, std::vector<Case> cases, std::shared_ptr<Block> defaultCase = nullptr)
      : expr(expr), cases(cases), defaultCase(defaultCase) {}

  /// @return expression used as value for the switch
  auto getExpr() const { return expr; }
  /// @return cases for the switch
  auto getCases() const { return cases; }
  /// @return default case for the switch
  auto getDefaultCase() const { return defaultCase; }

  // Set a visit handler for the generators
  SN_GENERATOR_VISITS
};

} // namespace ir
} // namespace snowball

#endif // __SNOWBALL_SWITCH_VALUE_H_
