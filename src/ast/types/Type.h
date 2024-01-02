
#include "../../common.h"
#include "../../ir/id.h"

#include <cassert>
#include <memory>
#include <string>
#include <vector>

#define SNOWBALL_TYPE_COPIABLE(X)                                                                                      \
  Type* copy() const override { return new X(*this); }

#ifndef __SNOWBALL_AST_TYPE_H_
#define __SNOWBALL_AST_TYPE_H_

#define SNOWBALL_MUTABLE_CAST_CHECK                                                                                    \
  if (!_mutable && ty->isMutable()) return false;

/**
 * Types in snowball can be represented in many different forms.
 * There can be user defined types (aka, classes and structs) and
 * there can be already built in primitive types.
 *
 * The purpose of this base type is to create a common group
 * for all of this kind of types.
 *
 * Each type should have atleast a function that generates it's
 * llvm ir equivalent of it.
 */
namespace snowball {

namespace Syntax {
namespace Expression {
class TypeRef;
}
}; // namespace Syntax

namespace types {
class ReferenceType;
class InterfaceType;

class Type {
protected:
  // Type's name
  std::string name;
  // Whether or not a type is mutable
  bool _mutable = false;
  // A type implementation
  std::vector<InterfaceType*> impls;

public:
  enum Kind
  {
    TYPE,
    CLASS,
    REF,
    INTERFACE,
    ENUM,
  } kind;

public:
  explicit Type(Kind p_kind, bool isMutable = false);
  explicit Type(Kind p_kind, std::string p_name, bool isMutable = false);

  Type& operator=(const Type&) = delete;
  Type(const Type& other) = default;

  ~Type() noexcept = default;

  /// @param other another type
  /// @return true if this type is equal to the argument type
  virtual bool is(Type* other) const { return getName() == other->getName(); }
  /// @return current's type name
  virtual std::string getName() const { return name; }
  /// @return type's pretty names, commonly used for output
  virtual std::string getPrettyName() const { return (_mutable ? "mut " : "") + name; };
  /// @return Get a mangled version of the current type
  virtual std::string getMangledName() const { return "T" + std::to_string(name.size()) + name; };

  /// @return if a type can be casted to this type
  virtual bool canCast(Type* ty) const { return false; }

  /// @brief Create a *new* reference type with this type as base
  /// @return a std::shared_ptr<ReferenceType> but casted into a `Type`
  virtual Type* getReferenceTo();
  /// @brief Create a *new* pointer type with this type as base
  /// @return a std::shared_ptr<PointerType> but casted into a `Type`
  virtual Type* getPointerTo(bool isMutable);

  /// @brief Create a new copy of this type
  /// @return a Type* but casted into a `Type`
  virtual Type* copy() const;

  /// @brief Transform the type into a syntax type reference node.
  ///	This is useful for cases such as class methods where the first
  /// argument needs to be "self" (aka. A type reference to it's
  /// parent class)
  virtual Syntax::Expression::TypeRef* toRef();

  /// @return If the function is mutable
  virtual bool isMutable() const { return _mutable; }
  /// @brief Set the mutability of the type
  virtual void setMutable(bool m);

  /// @return The size of the type in bytes
  virtual std::int64_t sizeOf() const { assert(!"called sizeOf to not-specialised type!"); }
  /// @return The alignment of the type in bytes
  virtual std::int64_t alignmentOf() const { assert(!"called alignmentOf to not-specialised type!"); }

  /// @brief Get the type's implementation
  std::vector<InterfaceType*> getImpls() const { return impls; }
  /// @brief Add a type implementation
  void addImpl(InterfaceType* impl) { impls.push_back(impl); }
};

}; // namespace types
}; // namespace snowball

#endif // __SNOWBALL_AST_TYPE_H_
