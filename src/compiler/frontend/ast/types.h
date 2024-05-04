
#ifndef __SNOWBALL_FRONTEND_AST_TYPES_H__
#define __SNOWBALL_FRONTEND_AST_TYPES_H__

#include <vector>
#include <string>
#include <cstddef>
#include <cassert>

#include "compiler/utils/id.h"
#include "compiler/frontend/location.h"
#include "compiler/frontend/ast/nodes/other.h"

namespace snowball {
namespace frontend {
namespace ast {
class ClassDecl;

namespace types {

class IntType;
class FloatType;
class FuncType;
class GenericType;
class ErrorType;
class UnknownType;
class VoidType;
class ClassType;

class Type {
public:
  virtual ~Type() = default;
#define CHILD(x, y) virtual y* as_##x() { return nullptr; } \
                    virtual bool is_##x() const { return false; }
  CHILD(int, IntType)
  CHILD(float, FloatType)
  CHILD(func, FuncType)
  CHILD(generic, GenericType)
  CHILD(error, ErrorType)
  CHILD(unknown, UnknownType)
  CHILD(void, VoidType)
  CHILD(class, ClassType)
#undef CHILD
  virtual std::string get_printable_name() const = 0;
  virtual std::string get_mangled_name() const = 0;
  virtual bool is_deep_unknown() const { return false; }
  virtual bool is_deep_generic() const { return false; }
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

  std::string get_printable_name() const override;
  std::string get_mangled_name() const override;
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

  std::string get_printable_name() const override;
  std::string get_mangled_name() const override;
};

class FuncType final : public Type {
  std::vector<Type*> param_types;
  Type* return_type;
  bool variadic = false;
public:
  FuncType(const std::vector<Type*>& param_types, Type* return_type, bool variadic)
    : param_types(param_types), return_type(return_type), variadic(variadic) {}
  ~FuncType() = default;

  auto& get_param_types() { return param_types; }
  auto& get_return_type() { return return_type; }

  static auto create(const std::vector<Type*>& param_types, Type* return_type, bool variadic) {
    return new FuncType(param_types, return_type, variadic);
  }

  FuncType* as_func() override { return this; }
  bool is_func() const override { return true; }
  bool is_variadic() const { return variadic; }

  std::string get_printable_name() const override;
  std::string get_mangled_name() const override;
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
  bool is_deep_generic() const override { return true; }

  std::string get_printable_name() const override;
  std::string get_mangled_name() const override;
};

class ErrorType final : public Type {
public:
  ErrorType() = default;
  ~ErrorType() = default;

  static auto create() { return new ErrorType(); }

  ErrorType* as_error() override { return this; }
  bool is_error() const override { return true; }

  std::string get_printable_name() const override;
  std::string get_mangled_name() const override;
};

class UnknownType final : public Type {
  size_t id;
public:
  UnknownType(size_t id) : id(id) {}
  ~UnknownType() = default;

  auto get_id() const { return id; }

  static auto create(std::vector<ast::types::Type*>& constrs) { 
    auto ty = new UnknownType(constrs.size());
    constrs.push_back(ty);
    return ty;
  }

  UnknownType* as_unknown() { return this; }
  bool is_unknown() const { return true; }
  bool is_deep_unknown() const override { return true; }

  std::string get_printable_name() const override;
  std::string get_mangled_name() const override;
};

class VoidType final : public Type {
public:
  VoidType() = default;
  ~VoidType() = default;

  static auto create() { return new VoidType(); }

  virtual VoidType* as_void() { return this; }
  virtual bool is_void() const { return true; }

  std::string get_printable_name() const override;
  std::string get_mangled_name() const override;
};

class ClassType final : public Type, public GenericNode<Type*>, public Identified,
  public LocationHolder {
  NamespacePath path;
  ast::ClassDecl* decl;
public:
  ClassType(ast::ClassDecl* decl, const NamespacePath& path, const std::vector<Type*>& generics, const SourceLocation& loc)
    : GenericNode<Type*>(generics), LocationHolder(loc), decl(decl), path(path) {}

  ~ClassType() = default;

  auto get_name() const { return path.get_last(); }
  auto get_path() const { return path; }
  auto get_decl() const { return decl; }

  static auto create(ast::ClassDecl* decl, const NamespacePath& path, const std::vector<Type*>& generics, const SourceLocation& loc) {
    return new ClassType(decl, path, generics, loc);
  }

  ClassType* as_class() override { return this; }
  bool is_class() const override { return true; }
  bool is_deep_unknown() const override; // It's unknown if any of the generics are unknown
  bool is_deep_generic() const override; // It's generic if any of the generics are generic

  std::string get_printable_name() const override;
  std::string get_mangled_name() const override;
};

}
}
}
}

#endif // __SNOWBALL_FRONTEND_AST_TYPES_H__
