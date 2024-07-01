
#ifndef __SNOWBALL_FRONTEND_AST_TYPES_H__
#define __SNOWBALL_FRONTEND_AST_TYPES_H__

#include <cassert>
#include <cstddef>
#include <string>
#include <vector>

#include "compiler/frontend/ast/nodes/other.h"
#include "compiler/frontend/location.h"
#include "compiler/utils/id.h"

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
class ReferenceType;
class PointerType;
class SelfType;
class ExtensibleType;

class Type {
  bool is_mutable = false;

public:
  virtual ~Type() = default;
#define CHILD(x, y)                                                                    \
  virtual y* as_##x() { return nullptr; }                                              \
  virtual bool is_##x() const { return false; }
  CHILD(int, IntType)
  CHILD(float, FloatType)
  CHILD(func, FuncType)
  CHILD(generic, GenericType)
  CHILD(error, ErrorType)
  CHILD(unknown, UnknownType)
  CHILD(void, VoidType)
  CHILD(class, ClassType)
  CHILD(reference, ReferenceType)
  CHILD(pointer, PointerType)
  CHILD(self_type, SelfType)
#undef CHILD
  virtual std::string get_printable_name() = 0;
  virtual std::string get_mangled_name() = 0;

  virtual bool is_deep_unknown() const { return false; }
  virtual bool is_deep_generic() const { return false; }

  virtual bool equals(Type* other, bool ignore_self = false);
  virtual bool equals_impl(Type* other, bool ignore_self) = 0;

  Type* get_reference_to();
  Type* get_pointer_to(bool is_const = false);

  bool is_mutable_type() const { return is_mutable; }
  unsigned int reference_depth();

  virtual bool is_copyable() const { return false; }

  virtual bool is_extensible() const { return false; }
  virtual ExtensibleType* as_extensible() { return nullptr; }

  Type() = default;
  Type(bool is_mutable) : is_mutable(is_mutable) {}
};

class ExtensibleType : public Identified, public Type {
public:
  template <typename... Args>
  ExtensibleType(Args&&... args) : Identified(std::forward<Args>(args)...) {}
  virtual ~ExtensibleType() = default;

  bool is_extensible() const override { return true; }
  ExtensibleType* as_extensible() override { return this; }

  // Use carefully
  void override_extensible_id(size_t id) { this->id = id; }
};

class IntType final : public ExtensibleType {
  unsigned int bits;
  bool _signed;

public:
  IntType(unsigned int bits, bool is_signed)
    : bits(bits)
    , _signed(is_signed) {}
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

  std::string get_printable_name() override;
  std::string get_mangled_name() override;

  bool is_copyable() const override { return true; }
  bool equals_impl(Type* other, bool ignore_self) override;
};

class FloatType final : public ExtensibleType {
  unsigned int bits;

public:
  FloatType(unsigned int bits)
    : bits(bits) {}
  ~FloatType() = default;

  auto get_bits() const { return bits; }

  static auto create(unsigned int bits) { return new FloatType(bits); }

  static auto create_f32() { return create(32); }
  static auto create_f64() { return create(64); }

  FloatType* as_float() override { return this; }
  bool is_float() const override { return true; }

  std::string get_printable_name() override;
  std::string get_mangled_name() override;

  bool is_copyable() const override { return true; }
  bool equals_impl(Type* other, bool ignore_self) override;
};

class FuncType final : public Type {
  std::optional<std::vector<Type*>> param_types_cache;
  Type* return_type;
  bool variadic = false;
  FnDecl* linked = nullptr;
  bool unsafe = false;

  bool cached = false;

public:
  FuncType(FnDecl* linked, Type* return_type, bool variadic, bool unsafe)
    : return_type(return_type), variadic(variadic), linked(linked), unsafe(unsafe) {}
  ~FuncType() = default;

  std::vector<Type*> get_param_types();
  auto& get_return_type() { return return_type; }

  static auto create(FnDecl* linked, Type* return_type, bool variadic = false, bool unsafe = false) {
    return new FuncType(linked, return_type, variadic, unsafe);
  }

  FuncType* as_func() override { return this; }
  bool is_func() const override { return true; }
  bool is_variadic() const { return variadic; }
  bool is_unsafe() const { return unsafe; }

  void recalibrate_cache();

  void mutate_return_type(Type* ty) { return_type = ty; }

  // Cache used by the binder to avoid re-compiling types over and over
  // It does not have any relation with the argument types-cache
  void set_cached() { cached = true; }
  bool is_cached() const { return cached; }

  std::string get_printable_name() override;
  std::string get_mangled_name() override;

  bool is_copyable() const override { return true; }
  bool equals_impl(Type* other, bool ignore_self) override;
};

class SelfType final : public Type {
  Type* self;

public:
  SelfType(Type* self)
    : self(self) {}
  ~SelfType() = default;

  auto get_self() const { return self; }

  static auto create(Type* self) { return new SelfType(self); }

  SelfType* as_self_type() override { return this; }
  bool is_self_type() const override { return true; }

  std::string get_printable_name() override;
  std::string get_mangled_name() override;

  bool equals_impl(Type* other, bool ignore_self) override;
};

class GenericType final : public Type {
  std::string name;
  std::vector<Type*> constraints;

public:
  GenericType(const std::string& name, const std::vector<Type*>& constraints)
    : name(name), constraints(constraints) {}
  ~GenericType() = default;

  auto get_name() const { return name; }
  void add_constraints(Type* ty) { constraints.push_back(ty); }
  auto get_constraints() const { return constraints; }

  static auto create(const std::string& name, const std::vector<Type*>& constraints = {}) { 
    return new GenericType(name, constraints); 
  }

  GenericType* as_generic() override { return this; }
  bool is_generic() const override { return true; }
  bool is_deep_generic() const override { return true; }

  std::string get_printable_name() override;
  std::string get_mangled_name() override;

  bool equals_impl(Type* other, bool ignore_self) override;
  bool is_copyable() const override;
};

class ErrorType final : public Type {
public:
  ErrorType() = default;
  ~ErrorType() = default;

  static auto create() { return new ErrorType(); }

  ErrorType* as_error() override { return this; }
  bool is_error() const override { return true; }

  std::string get_printable_name() override;
  std::string get_mangled_name() override;

  bool equals_impl(Type* other, bool ignore_self) override { return other->is_error(); }
};

class UnknownType final : public Type {
  size_t id;

public:
  UnknownType(size_t id)
    : id(id) {}
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

  std::string get_printable_name() override;
  std::string get_mangled_name() override;

  bool equals_impl(Type* other, bool ignore_self) override;
};

class VoidType final : public Type {
public:
  VoidType() = default;
  ~VoidType() = default;

  static auto create() { return new VoidType(); }

  virtual VoidType* as_void() { return this; }
  virtual bool is_void() const { return true; }

  std::string get_printable_name() override;
  std::string get_mangled_name() override;

  bool is_copyable() const override { return true; }
  bool equals_impl(Type* other, bool ignore_self) override { return other->is_void(); }
};

class ClassType final : public ExtensibleType, public GenericNode<Type*>, public LocationHolder {
  NamespacePath path;
  ast::ClassDecl* decl;

  std::vector<uint64_t> vtable;

public:
  ClassType(
    ast::ClassDecl* decl, const NamespacePath& path,
    const std::vector<Type*>& generics, const SourceLocation& loc
  ) : GenericNode<Type*>(generics), LocationHolder(loc), decl(decl), path(path) {}

  ~ClassType() = default;

  auto get_name() const { return path.get_last(); }
  auto get_path() const { return path; }
  auto get_decl() const { return decl; }

  bool is_interface_decl() const;
  bool is_class_decl() const;

  auto& get_vtable() { return vtable; }
  void add_vtable_entry(uint64_t id) { vtable.push_back(id); }

  static auto
  create(ast::ClassDecl* decl, const NamespacePath& path,
         const std::vector<Type*>& generics, const SourceLocation& loc) {
    return new ClassType(decl, path, generics, loc);
  }

  ClassType* as_class() override { return this; }
  bool is_class() const override { return true; }
  bool
  is_deep_unknown() const override; // It's unknown if any of the generics are unknown
  bool
  is_deep_generic() const override; // It's generic if any of the generics are generic

  std::string get_printable_name() override;
  std::string get_mangled_name() override;

  bool equals_impl(Type* other, bool ignore_self) override;
};

class ReferenceType final : public Type {
  Type* ref;

public:
  ReferenceType(Type* ref) : ref(ref) {}
  ~ReferenceType() = default;

  auto get_ref() const { return ref; }
  auto& get_mut_ref() { return ref; }

  static auto create(Type* ref) { return new ReferenceType(ref); }

  ReferenceType* as_reference() override { return this; }
  bool is_reference() const override { return true; }

  std::string get_printable_name() override;
  std::string get_mangled_name() override;

  bool is_deep_unknown() const override { return ref->is_deep_unknown(); }
  bool is_deep_generic() const override { return ref->is_deep_generic(); }

  bool is_copyable() const override { return true; }
  bool equals_impl(Type* other, bool ignore_self) override;
};

class PointerType final : public ExtensibleType {
  Type* pointee;

public:
  PointerType(Type* pointee, bool is_const)
    : ExtensibleType(!is_const), pointee(pointee) {}
  ~PointerType() = default;

  auto get_pointee() const { return pointee; }
  auto& get_mut_pointee() { return pointee; }

  static auto create(Type* pointee, bool is_const = false) {
    return new PointerType(pointee, is_const);
  }

  PointerType* as_pointer() override { return this; }
  bool is_pointer() const override { return true; }

  std::string get_printable_name() override;
  std::string get_mangled_name() override;

  bool is_deep_unknown() const override { return pointee->is_deep_unknown(); }
  bool is_deep_generic() const override { return pointee->is_deep_generic(); }

  bool is_copyable() const override { return true; }
  bool equals_impl(Type* other, bool ignore_self) override;
};

} // namespace types
} // namespace ast
} // namespace frontend
} // namespace snowball

#endif // __SNOWBALL_FRONTEND_AST_TYPES_H__
