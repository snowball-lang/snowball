
#include "../../common.h"
#include "../../constants.h"
#include "../../utils/utils.h"
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
  SNOWBALL_TYPE_COPIABLE(PrimitiveType)
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
  virtual bool canCast(Type* ty) const override { return NumericType::isNumericType(ty); }

public:
  /**
   * @brief Check if a type is numeric.
   * @note These are the numberic types:
   *  ints: i[N], i64, i32, i16, i8,
   *  floats: f64, f32,
   *  boolean: i1
   */
  static bool isNumericType(Type* ty);
  SNOWBALL_TYPE_COPIABLE(NumericType)
};

/// @brief Representation of a void type.
class VoidType : public AcceptorExtend<VoidType, PrimitiveType> {
public:
  VoidType() : AcceptorExtend(SN_VOID_TYPE) { }
  SNOWBALL_TYPE_COPIABLE(VoidType)

  virtual std::int64_t sizeOf() const override { return 0; }
  virtual std::int64_t alignmentOf() const override { return 0; }
};

/// @brief String (represents int 8 pointer)
class CharType : public AcceptorExtend<CharType, NumericType> {
public:
  CharType() : AcceptorExtend(SN_CHR_TYPE) { }
  SNOWBALL_TYPE_COPIABLE(CharType)

  virtual std::int64_t sizeOf() const override { return 1; }
  virtual std::int64_t alignmentOf() const override { return 1; }
};

/// @brief Float (N) (represents N-bit floating point)
class FloatType : public AcceptorExtend<FloatType, NumericType> {
  std::int32_t bits;

public:
  FloatType(std::int32_t bits) : bits(bits), AcceptorExtend("f" + std::to_string(bits)) { }
  std::int32_t getBits() const { return bits; }
  SNOWBALL_TYPE_COPIABLE(FloatType)

  virtual std::int64_t sizeOf() const override { return bits / 8; }
  virtual std::int64_t alignmentOf() const override { return bits / 8; }
};

/**
 * Int (N) (represents N-bit signed integer)
 * @note This is a base class for all integer types.
 */
class IntType : public AcceptorExtend<IntType, NumericType> {
  std::int32_t bits;

public:
  IntType(std::int32_t bits) : bits(bits), AcceptorExtend(bits == 1 ? "bool" : "i" + std::to_string(bits)) { }
  std::int32_t getBits() const { return bits; }
  SNOWBALL_TYPE_COPIABLE(IntType)

  virtual std::int64_t sizeOf() const override { return bits == 1 ? 1 : (std::int64_t)(bits / 8); }
  virtual std::int64_t alignmentOf() const override { return bits == 1 ? 1 : (std::int64_t)(bits / 8); }
};

/// @brief Utility method to check if a type is an integer type.
static bool isIntType(Type* ty, std::int32_t bits = 32) {
  if (auto x = utils::cast<IntType>(ty)) return x->getBits() == bits;
  return false;
}

static bool isInt32Type(Type* ty) { return isIntType(ty, 32); }

/// @brief Utility method to check if a type is a float type.
static bool isFloatType(Type* ty, std::int32_t bits = 32) {
  if (auto x = utils::cast<FloatType>(ty)) return x->getBits() == bits;
  return false;
}

static bool isFloat32Type(Type* ty) { return isFloatType(ty, 32); }
static bool isDoubleType(Type* ty) { return isFloatType(ty, 64); }

}; // namespace types
}; // namespace snowball

#endif // __SNOWBALL_AST_PRIMITIVE_TYPE_H_
