
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
  /// @brief C-style switch case
  struct CStyleCase {
    /// @brief Value to compare
    std::shared_ptr<Value> value;
    /// @brief Block to jump to
    std::shared_ptr<Block> block;
  };
 private:
  /// @brief Expression used as value for the switch
  std::shared_ptr<Value> expr = nullptr;
  /// @brief Cases for the switch
  std::pair<std::vector<Case>, std::vector<CStyleCase>> cases;
  /// @brief Default case for the switch
  std::shared_ptr<Block> defaultCase = nullptr;
  /// @brief If the switch is a C-style switch
  bool cStyleSwitch = false;

 public:
  explicit Switch(std::shared_ptr<Value> expr, std::vector<Case> cases, std::shared_ptr<Block> defaultCase = nullptr)
    : expr(std::move(expr)), cases(std::move(cases), {}), defaultCase(std::move(defaultCase)) {}
  explicit Switch(std::shared_ptr<Value> expr, std::vector<CStyleCase> cases,
                  std::shared_ptr<Block> defaultCase = nullptr)
    : expr(std::move(expr)), cases({}, std::move(cases)), defaultCase(std::move(defaultCase)), cStyleSwitch(true) {}

  /// @return expression used as value for the switch
  auto getExpr() const { return expr; }
  /// @return cases for the switch
  auto getCases() const { return cases; }
  /// @return default case for the switch
  auto getDefaultCase() const { return defaultCase; }
  /// @return if the switch is a C-style switch
  auto isCStyleSwitch() const { return cStyleSwitch; }

  // Set a visit handler for the generators
  SN_GENERATOR_VISITS
};

} // namespace ir
} // namespace snowball

#endif // __SNOWBALL_SWITCH_VALUE_H_
