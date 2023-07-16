
#include "../../ValueVisitor/Visitor.h"
#include "../../ast/syntax/nodes.h"
#include "../../ast/types/DefinedType.h"
#include "../../ast/types/Type.h"
#include "../../ast/types/TypeAlias.h"
#include "../../common.h"
#include "Value.h"

#include <map>
#include <vector>

#ifndef __SNOWBALL_INDEX_EXTRACT_VALUE_H_
#define __SNOWBALL_INDEX_EXTRACT_VALUE_H_

namespace snowball {
namespace ir {

/**
 * @brief Representation of an index extraction statement
 *  in the IR.
 */
class IndexExtract : public AcceptorExtend<IndexExtract, Value> {
    // Expression used as value for the index statement
    std::shared_ptr<Value> value;
    // Index were the extraction is taken place.
    unsigned int index;
    // Field being extracted from
    types::DefinedType::ClassField* field;

  public:
    explicit IndexExtract(std::shared_ptr<Value> value, types::DefinedType::ClassField* field, unsigned int i)
        : value(value), index(i), field(field){};

    /**
     * @return The value it's being extracted
     *  from.
     */
    auto getValue() const { return value; }
    /**
     * @brief Get the index used for the index
     *  extraction
     */
    virtual unsigned int getIndex() const { return index; }
    /**
     * @brief Get the field object from the value we are
     *  trying to extract
     */
    virtual types::DefinedType::ClassField* getField() const { return field; }

    // Set a visit handler for the generators
    SN_GENERATOR_VISITS
};

} // namespace ir
} // namespace snowball

#endif // __SNOWBALL_INDEX_EXTRACT_VALUE_H_
