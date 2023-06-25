
#include "../../common.h"
#include "../../constants.h"
#include "Type.h"

#include <string>

#ifndef __SNOWBALL_AST_PRIMITIVE_TYPE_H_
#define __SNOWBALL_AST_PRIMITIVE_TYPE_H_

#define SN_BOOL_TYPE  "bool"
#define SN_STR_TYPE   "String"
#define SN_CHR_TYPE   "char"
#define SN_INT64_TYPE "i64"
#define SN_INT32_TYPE "i32"
#define SN_INT16_TYPE "i16"
#define SN_INT8_TYPE  "i8"
#define SN_F64_TYPE   "f64"
#define SN_F32_TYPE   "f32"
#define SN_COB_TYPE   "cobj"
#define SN_VOID_TYPE  "void"

/**
 * Primitive types are those types who differ from
 * user defined types. These types are not constructed.
 *
 * These types often refers to a limited set of data
 * in use by a particular preprocessor.
 *
 * There are: null, int, string, float, etc...
 */
namespace snowball {
namespace types {
class PrimitiveType : public AcceptorExtend<PrimitiveType, Type> {
  public:
    PrimitiveType(std::string p_name) : AcceptorExtend(Kind::TYPE, p_name) { }
};

/**
 * @brief This is a primitive type that acts like
 *  a numeric type. (e.g. i32, f64, bool, etc...)
 */
class NumericType : public AcceptorExtend<NumericType, PrimitiveType> {
  public:
    NumericType(std::string p_name) : AcceptorExtend(p_name){};

    /// @brief override function. All numeric types
    ///  can cast to any other numeric types.
    bool canCast(Type* ty) const override { return NumericType::isNumericType(ty); }

  public:
    /**
     * @brief Check if a type is numeric.
     * @note These are the numberic types:
     *  ints: i[N], i64, i32, i16, i8,
     *  floats: f64, f32,
     *  boolean: i1
     */
    static bool isNumericType(Type* ty);
};

/// @brief Representation of a void type.
class VoidType : public AcceptorExtend<VoidType, PrimitiveType> {
  public:
    VoidType() : AcceptorExtend(SN_VOID_TYPE) { }
};

/// @brief C object pointer type (it's the equivalent of `void*` in C)
class CObjectType : public AcceptorExtend<CObjectType, PrimitiveType> {
  public:
    CObjectType() : AcceptorExtend(SN_COB_TYPE) { }
};

/// @brief Bool (represents 1-bit signed integer)
class BoolType : public AcceptorExtend<BoolType, NumericType> {
  public:
    BoolType() : AcceptorExtend(SN_BOOL_TYPE) { }
};

/// @brief String (represents int 8 pointer)
class CharType : public AcceptorExtend<CharType, NumericType> {
  public:
    CharType() : AcceptorExtend(SN_CHR_TYPE) { }
};

/// @brief Float 64 (represents 64-bit floating point)
class Float64Type : public AcceptorExtend<Float64Type, NumericType> {
  public:
    Float64Type() : AcceptorExtend(SN_F64_TYPE) { }
};

/// @brief Float 32 (represents 32-bit floating point)
class Float32Type : public AcceptorExtend<Float32Type, NumericType> {
  public:
    Float32Type() : AcceptorExtend(SN_F32_TYPE) { }
};

/// @brief Int 64 (represents 64-bit signed integer)
class Int64Type : public AcceptorExtend<Int64Type, NumericType> {
  public:
    Int64Type() : AcceptorExtend(SN_INT64_TYPE) { }
};

/// @brief Int 16 (represents 16-bit signed integer)
class Int16Type : public AcceptorExtend<Int16Type, NumericType> {
  public:
    Int16Type() : AcceptorExtend(SN_INT16_TYPE) { }
};

/// @brief Int 8 (represents 8-bit signed integer)
class Int8Type : public AcceptorExtend<Int8Type, NumericType> {
  public:
    Int8Type() : AcceptorExtend(SN_INT8_TYPE) { }
};

/**
 * Int 32 (represents 32-bit signed integer)
 *
 * One differentiation that this type has with the other types
 * is that int 32 has it’s unique type name and it’s alias name.
 * It’s former type name is “i32” but it’s alias is “Int”. This
 * is because it adds a way for users to have a more high-level
 * experience in snowball.
 */
class Int32Type : public AcceptorExtend<Int32Type, NumericType> {
  public:
    static const std::string TYPE_ALIAS;

    Int32Type() : AcceptorExtend(SN_INT32_TYPE) { }

    bool is(Type* other) const override {
        return (TYPE_ALIAS == other->getName()) || NumericType::is(other);
    }
};

inline const std::string Int32Type::TYPE_ALIAS = "int";
}; // namespace types
}; // namespace snowball

#endif // __SNOWBALL_AST_PRIMITIVE_TYPE_H_
