
#include "../../ValueVisitor/Visitor.h"
#include "../../ast/syntax/nodes.h"
#include "../../ast/types/Type.h"
#include "Value.h"

#include <map>
#include <vector>

#ifndef __SNOWBALL_LOOP_FLOW_H_
#define __SNOWBALL_LOOP_FLOW_H_

namespace snowball {
namespace ir {

/**
 * @brief Representation of a loop flow statement in the IR.
 */
class LoopFlow : public AcceptorExtend<LoopFlow, Value> {
public:
  using Type = Syntax::Statement::LoopFlow::FlowType;
private:
  Type flowType;
public:
  explicit LoopFlow(Type type) : flowType(type){};

  /**
   * @return The type of the loop flow statement.
   */
  auto getFlowType() const { return flowType; }

  // Set a visit handler for the generators
  SN_GENERATOR_VISITS
};

using LoopFlowType = LoopFlow::Type;

} // namespace ir
} // namespace snowball

#endif // __SNOWBALL_LOOP_FLOW_H_
