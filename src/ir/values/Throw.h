
#include "../../ValueVisitor/Visitor.h"
#include "../../ast/syntax/nodes.h"
#include "../../ast/types/Type.h"
#include "../../common.h"
#include "Value.h"

#include <map>
#include <vector>

#ifndef __SNOWBALL_THROW_VALUE_H_
#define __SNOWBALL_THROW_VALUE_H_

namespace snowball {
namespace ir {

/**
 * @brief Representation of a throw statement in the IR.
 * @note This is not the same as the throw statement in C++.
 * This is more like the throw statement in Java.
 * @see https://docs.oracle.com/javase/tutorial/essential/exceptions/throwing.html
 */
class Throw : public AcceptorExtend<Throw, Value> {
  // Expression used as value for the throw statement
  std::shared_ptr<Value> expr = nullptr;

public:
  explicit Throw(std::shared_ptr<Value> expr) : expr(expr){};

  /**
   * @return value to throw
   * @note The value may be std::nullptr because
   *  the user might do `throw;` for void functions
   */
  auto getExpr() { return expr; }

  // Set a visit handler for the generators
  SN_GENERATOR_VISITS
};

} // namespace ir
} // namespace snowball

#endif // __SNOWBALL_RETURN_VALUE_H_
