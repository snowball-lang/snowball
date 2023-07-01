
#include "../../ValueVisitor/Visitor.h"
#include "../../ast/syntax/nodes.h"
#include "../../ast/types/DefinedType.h"
#include "../../ast/types/Type.h"
#include "../../common.h"
#include "Value.h"

#include <map>
#include <vector>

#ifndef __SNOWBALL_REFERENCE_TO_VALUE_H_
#define __SNOWBALL_REFERENCE_TO_VALUE_H_

namespace snowball {
namespace ir {

/**
 * @brief Representation of a reference to a value in the IR.
 */
class ReferenceTo : public AcceptorExtend<ReferenceTo, Value> {
    // Expression used as value for the reference statement
    std::shared_ptr<Value> value;

  public:
    explicit ReferenceTo(std::shared_ptr<Value> value)
        : value(value) {};

    /**
     * @return The value it's being referenced to from. 
     */
    auto getValue() const { return value; }

    // Set a visit handler for the generators
    SN_GENERATOR_VISITS
};

} // namespace ir
} // namespace snowball

#endif // __SNOWBALL_REFERENCE_TO_VALUE_H_
