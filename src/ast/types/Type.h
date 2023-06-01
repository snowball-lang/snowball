
#include "../../common.h"

#include <memory>
#include <string>

#ifndef __SNOWBALL_AST_BASE_TYPE_H_
#define __SNOWBALL_AST_BASE_TYPE_H_

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
class PointerType;

class Type : public std::enable_shared_from_this<Type> {
  protected:
    // Type's name
    std::string name;

  public:
    enum Kind { TYPE, CLASS, REF } kind;

  public:
    explicit Type(Kind p_kind) : kind(p_kind) {}
    explicit Type(Kind p_kind, std::string p_name)
        : kind(p_kind), name(p_name) {}

    Type(const Type&)            = delete;
    Type& operator=(const Type&) = delete;

    ~Type() noexcept = default;

    /// @param other another type
    /// @return true if this type is equal to the argument type
    virtual bool is(Type *other) { return getName() == other->getName(); }
    /// @brief normal Type::is but with std::shared_ptr support
    virtual bool is(std::shared_ptr<Type> other) { return is(other.get()); }

    /// @return current's type name
    virtual std::string getName() const { return name; }
    /// @return type's pretty names, commonly used for output
    virtual std::string getPrettyName() const { return name; };
    /// @return Get a mangled version of the current type
    virtual std::string getMangledName() const {
        return "T" + std::to_string(name.size()) + name;
    };

    /// @return if a type can be casted to this type
    virtual bool canCast(Type *ty) const { return false; }
    /// @brief std::shared_ptr support for Type::canCast
    virtual bool canCast(std::shared_ptr<Type> t) const { return canCast(t.get()); }

    /// @brief Create a *new* pointer type with this type as base 
    /// @return a std::shared_ptr<PointerType> but casted into a `Type`
    virtual std::shared_ptr<Type> getPointerTo();

    /// @brief Transform the type into a syntax type reference node.
    ///	This is useful for cases such as class methods where the first
    /// argument needs to be "self" (aka. A type reference to it's
    /// parent class)
    virtual Syntax::Expression::TypeRef *toRef();
};
}; // namespace types
}; // namespace snowball

#endif // __SNOWBALL_AST_BASE_TYPE_H_
