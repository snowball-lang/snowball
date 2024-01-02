
#include "../../ValueVisitor/Visitor.h"
#include "../../ast/syntax/nodes.h"
#include "../../ast/types/DefinedType.h"
#include "../../ast/types/Type.h"
#include "../../ast/types/TypeAlias.h"
#include "../../common.h"
#include "Value.h"

#include <map>
#include <vector>

#ifndef __SNOWBALL_ENUM_INIT_H_
#define __SNOWBALL_ENUM_INIT_H_

namespace snowball {
namespace ir {

/**
 * @brief Enum initialization in the IR.
 */
class EnumInit : public AcceptorExtend<EnumInit, Value> {
  // Enum field name
  std::string name;

public:
  explicit EnumInit(std::string name) : name(name){};

  /**
   * @return The name of the enum field.
   */
  auto getName() const { return name; }

  // Set a visit handler for the generators
  SN_GENERATOR_VISITS
};


} // namespace ir
} // namespace snowball

#endif // __SNOWBALL_ENUM_INIT_H_
