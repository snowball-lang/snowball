
#ifndef __SNOWBALL_FRONTEND_AST_TYPES_H__
#define __SNOWBALL_FRONTEND_AST_TYPES_H__

#include <vector>
#include <string>
#include <cstddef>

namespace snowball {
namespace frontend {
namespace ast {
namespace types {

class IntType;
class FloatType;
class FuncType;
class GenericType;
class ErrorType;
class UnknownType;
class VoidType;

class Type {
public:
  virtual ~Type() = default;

  virtual IntType* as_int() { return nullptr; }
  virtual FloatType* as_float() { return nullptr; }
  virtual FuncType* as_func() { return nullptr; }
  virtual GenericType* as_generic() { return nullptr; } 
  virtual ErrorType* as_error() { return nullptr; }
  virtual UnknownType* as_unknown() { return nullptr; }
  virtual VoidType* as_void() { return nullptr; }

  virtual bool is_int() const { return false; }
  virtual bool is_float() const { return false; }
  virtual bool is_func() const { return false; }
  virtual bool is_generic() const { return false; }
  virtual bool is_error() const { return false; }
  virtual bool is_unknown() const { return false; }
  virtual bool is_void() const { return false; }
};

class IntType final : public Type {
  unsigned int bits;
  bool _signed;
public:
  IntType(unsigned int bits, bool is_signed)  
    : bits(bits), _signed(is_signed) {}
  ~IntType() = default;

  auto get_bits() const { return bits; }
  auto is_signed() const { return _signed; }

  static auto create(unsigned int bits, bool is_signed = true) {
    return new IntType(bits, is_signed);
  }

  static auto create_i8() { return create(8, true); }
  static auto create_i16() { return create(16, true); }
  static auto create_i32() { return create(32, true); }
  static auto create_i64() { return create(64, true); }
  static auto create_u8() { return create(8, false); }
  static auto create_u16() { return create(16, false); }
  static auto create_u32() { return create(32, false); }
  static auto create_u64() { return create(64, false); }

  IntType* as_int() override { return this; }
  bool is_int() const override { return true; }
};

class FloatType final : public Type {
  unsigned int bits;
public:
  FloatType(unsigned int bits) : bits(bits) {}
  ~FloatType() = default;

  auto get_bits() const { return bits; }

  static auto create(unsigned int bits) {
    return new FloatType(bits);
  }

  static auto create_f32() { return create(32); }
  static auto create_f64() { return create(64); }

  FloatType* as_float() override { return this; }
  bool is_float() const override { return true; }
};

class FuncType final : public Type {
  std::vector<Type*> param_types;
  Type* return_type;
public:
  FuncType(const std::vector<Type*>& param_types, Type* return_type) 
    : param_types(param_types), return_type(return_type) {}
  ~FuncType() = default;

  auto get_param_types() const { return param_types; }
  auto get_return_type() const { return return_type; }

  static auto create(const std::vector<Type*>& param_types, Type* return_type) {
    return new FuncType(param_types, return_type);
  }

  FuncType* as_func() override { return this; }
  bool is_func() const override { return true; }
};

class GenericType final : public Type {
  std::string name;
public:
  GenericType(const std::string& name) : name(name) {}
  ~GenericType() = default;

  auto get_name() const { return name; }

  static auto create(const std::string& name) {
    return new GenericType(name);
  }

  GenericType* as_generic() override { return this; }
  bool is_generic() const override { return true; }
};

class ErrorType final : public Type {
public:
  ErrorType() = default;
  ~ErrorType() = default;

  static auto create() { return new ErrorType(); }

  ErrorType* as_error() override { return this; }
  bool is_error() const override { return true; }
};

class UnknownType final : public Type {
  size_t id;
public:
  UnknownType(size_t id) : id(id) {}
  ~UnknownType() = default;

  auto get_id() const { return id; }

  static auto create(size_t id) { return new UnknownType(id); }

  UnknownType* as_unknown() { return this; }
  bool is_unknown() const { return true; }
};

class VoidType final : public Type {
public:
  VoidType() = default;
  ~VoidType() = default;

  static auto create() { return new VoidType(); }

  virtual VoidType* as_void() { return this; }
  virtual bool is_void() const { return true; }
};

}
}
}
}

#endif // __SNOWBALL_FRONTEND_AST_TYPES_H__
