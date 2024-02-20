
#ifndef __SNOWBALL_FRONTEND_AST_TYPES_H__
#define __SNOWBALL_FRONTEND_AST_TYPES_H__

namespace snowball {
namespace frontend {
namespace ast {
namespace types {

class IntType;
class FloatType;
class FunctionType;
class GenericType;

class Type {
public:
  virtual ~Type() = default;

  virtual IntType* as_int() { return nullptr; }
  virtual FloatType* as_float() { return nullptr; }
  virtual FunctionType* as_function() { return nullptr; }
  virtual GenericType* as_generic() { return nullptr; } 
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
};

class FunctionType final : public Type {
  std::vector<Type*> param_types;
  Type* return_type;
public:
  FunctionType(const std::vector<Type*>& param_types, Type* return_type) 
    : param_types(param_types), return_type(return_type) {}
  ~FunctionType() = default;

  auto get_param_types() const { return param_types; }
  auto get_return_type() const { return return_type; }

  static auto create(const std::vector<Type*>& param_types, Type* return_type) {
    return new FunctionType(param_types, return_type);
  }

  FunctionType* as_function() override { return this; }
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

  virtual GenericType* as_generic() override { return this; }
};

}
}
}
}

#endif // __SNOWBALL_FRONTEND_AST_TYPES_H__
