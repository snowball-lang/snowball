
#include "../../ValueVisitor/Visitor.h"
#include "../../ast/syntax/nodes.h"
#include "../../ast/types/Type.h"
#include "../../common.h"
#include "Body.h"
#include "Value.h"

#include <map>
#include <vector>

#ifndef __SNOWBALL_CONSTANT_VALUES_H_
#define __SNOWBALL_CONSTANT_VALUES_H_

namespace snowball {
namespace ir {

/// @brief Representation of a constant value in the IR
class ConstantValue : public AcceptorExtend<ConstantValue, Value> {
  public:
    enum ConstantType {
#include "../../defs/ct.def"
    };

    ConstantValue(ConstantType ty) : type(ty) {}
    // Get constant value's type
    auto getConstantType() { return type; }

  private:
    // Type value to differentiate between constantss
    ConstantType type;
};

/// @brief Constant representation of a string
class StringValue : public AcceptorExtend<StringValue, ConstantValue> {
    // Value stored from the AST
    std::string value;

  public:
    // Create a new string value for the IR
    StringValue(std::string value) : AcceptorExtend(String), value(value) {}

    // Get the string value.
    auto getConstantValue() const { return value; }
    // Set a visit handler for the generators
    SN_GENERATOR_VISITS
};

/// @brief Constant representation of an integer (32-bits)
class NumberValue : public AcceptorExtend<NumberValue, ConstantValue> {
    // Value stored from the AST
    snowball_int_t value;

  public:
    // Create a new number constant for the IR
    NumberValue(snowball_int_t value) : AcceptorExtend(Number), value(value) {}

    // Get the number value.
    auto getConstantValue() const { return value; }
    // Set a visit handler for the generators
    SN_GENERATOR_VISITS
};

/// @brief Constant representation of a float (32-bits)
class FloatValue : public AcceptorExtend<FloatValue, ConstantValue> {
    // Value stored from the AST
    double value;

  public:
    // Create a new floating number for the IR
    FloatValue(double value) : AcceptorExtend(Float), value(value) {}

    // Get the number value.
    auto getConstantValue() const { return value; }
    // Set a visit handler for the generators
    SN_GENERATOR_VISITS
};

/// @brief Constant representation of a boolean
class BooleanValue : public AcceptorExtend<BooleanValue, ConstantValue> {
    // Value stored from the AST
    bool value;

  public:
    // Create a new boolean value for the IR
    BooleanValue(bool value) : AcceptorExtend(String), value(value) {}

    // Get the boolean value.
    auto getConstantValue() const { return value; }
    // Set a visit handler for the generators
    SN_GENERATOR_VISITS
};

/// @brief Constant representation of a character (8-bit ints)
class CharValue : public AcceptorExtend<BooleanValue, ConstantValue> {
    // Value stored from the AST
    char value;

  public:
    // Create a new boolean value for the IR
    CharValue(char value) : AcceptorExtend(Char), value(value) {}

    // Get the boolean value.
    auto getConstantValue() const { return value; }
    // Set a visit handler for the generators
    SN_GENERATOR_VISITS
};

} // namespace ir
} // namespace snowball

#endif // __SNOWBALL_CONSTANT_VALUES_H_
