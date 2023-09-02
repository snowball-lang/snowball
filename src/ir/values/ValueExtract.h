
#include "../../ValueVisitor/Visitor.h"
#include "../../ast/syntax/nodes.h"
#include "../../ast/types/Type.h"
#include "../../common.h"
#include "Value.h"

#include <map>
#include <vector>

#ifndef __SNOWBALL_VALUE_EXTRACT_VALUE_H_
#define __SNOWBALL_VALUE_EXTRACT_VALUE_H_

namespace snowball {
namespace ir {

/**
 * @brief A value extract represents the use of (e.g.) an
 * identifier.
 */
class ValueExtract : public AcceptorExtend<ValueExtract, Value> {
  // Value being extracted
  std::shared_ptr<Value> value;

 public:
  explicit ValueExtract(std::shared_ptr<Value> variable) : value(variable){};

  /// @return The stored value
  auto getValue() { return value; }

  // Set a visit handler for the generators
  SN_GENERATOR_VISITS
};

} // namespace ir
} // namespace snowball

#endif // __SNOWBALL_VALUE_EXTRACT_VALUE_H_
