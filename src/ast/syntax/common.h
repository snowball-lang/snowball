

#include "../../common.h"
#include "../../sourceInfo/DBGSourceInfo.h"

#include <assert.h>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>
#include <optional>

#ifndef __SNOWBALL_AST_COMMON_NODES_H_
#define __SNOWBALL_AST_COMMON_NODES_H_

#include "../types/Type.h"

#define ACCEPT() void accept(Syntax::Visitor* v) override;

namespace snowball {

/// @brief An enum representing the attributes that can be stored
///  for a node.
enum Attributes {
  // Default attributes
  INVALID,
  CFG,
  ATTR,

  // FUNCTION ATTRIBUTES
  TEST,
  BENCH,
  LLVM_FUNC,
  INTERNAL_LINKAGE,
  EXTERNAL_LINKAGE,
  INLINE,
  NO_INLINE,
  NO_MANGLE,
  NOT_IMPLEMENTED,
  EXPORT,
  OVERRIDE,
  FIRST_ARG_IS_SELF,
  EXPLICIT,
  UNSAFE_FUNC_NOT_BODY,
  UNSAFE, // also used for blocks

  // Builting related attributes
  BUILTIN,
  NO_POINTER_SELF,
  INTRINSIC,

  // Function internal attributes
  TYPECHECKED,
  ALLOW_FOR_TEST,
  ALLOW_FOR_BENCH,

  // Class attributes
  CLASS_EXTENDS,
  NO_CONSTRUCTOR,

  // Import attributes
  MACROS,
};

namespace Syntax {
namespace transform {
struct MacroInstance;
}
// Forward declarations
class Visitor;
class WhereClause;

/**
 * A generic class that accepts an enum as a template parameter and
 * stores and checks attributes for a node.
 */
class AttributeHolder {
  using StoreType = std::unordered_map<std::string, std::string>;
  std::unordered_map<Attributes, StoreType> arguments;

 public:
  /**
   * Checks if a specific attribute is set for the node.
   *
   * @param attribute The attribute to check.
   * @return True if the attribute is set, false otherwise.
   */
  bool hasAttribute(Attributes attribute) const { return (m_attributes & (1 << static_cast<int>(attribute))) != 0; }
  /**
   * Sets the bit for a specific attribute in the `m_attributes`
   * variable.
   *
   * @param attribute The attribute to add.
   */
  auto addAttribute(Attributes attribute, StoreType args = {}) {
    arguments[attribute] = args;
    return m_attributes |= (1 << static_cast<int>(attribute));
  }
  /**
   * Sets a new list of attributes to the current holder
   */
  void setAttributes(unsigned int attribute, std::unordered_map<Attributes, StoreType>& args) {
    m_attributes = attribute;
    arguments = args;
  }
  /**
   * Returns the respective unsigned integer for the attributes
   */
  auto getAttributes() const { return m_attributes; }
  /**
   * Returns all the arguments for the attributes
   */
  auto& getAllAttributeArgs() { return arguments; }
  /**
   * Sets the attributes from a holder
   */
  void setAttributes(AttributeHolder* holder) {
    arguments = std::move(holder->getAllAttributeArgs());
    m_attributes = holder->m_attributes;
  }
  /**
   * Clears the bit for a specific attribute in the `m_attributes`
   * variable.
   *
   * @param attribute The attribute to remove.
   */
  void removeAttribute(Attributes attribute) { m_attributes &= ~(1 << static_cast<int>(attribute)); }
  /**
   * Clears all attributes for the node by setting `m_attributes`
   * to zero.
   */
  void clearAttributes() { m_attributes = 0; }

  /**
   * Gets the arguments for a specific attribute.
   * @param attribute The attribute to get the arguments for.
   * @return A vector containing the arguments for the attribute.
   */
  StoreType getAttributeArgs(Attributes attribute) const {
    auto it = arguments.find(attribute);
    if (it == arguments.end()) return {};
    return it->second;
  }
  /**
   * Get attr value
   */
  std::optional<std::string> getAttrValue(std::string attrName) {
    if (hasAttribute(Attributes::ATTR)) {
      auto args = getAttributeArgs(Attributes::ATTR);
      auto it = args.find(attrName);
      if (it != args.end()) return it->second;
    }
    return std::nullopt;
  }

 private:
  /** The bit field storing the attributes for the node. */
  unsigned int m_attributes = 0;
};

struct Macro;

struct Node : public DBGObject, public AttributeHolder {
 public:
  Node() = default;
  ~Node() noexcept = default;

  virtual void accept(Syntax::Visitor* v) = 0;

  transform::MacroInstance* parentMacro = nullptr;
  /// @brief A flag that tells if the current node is
  ///  an operator
  bool isOperator = false;
};

/**
 * @brief This namespaces are used just for the more "generic"
 *  classes that can be inherited to make my life easier.
 */

namespace Expression {
struct Base : public AcceptorExtend<Base, Node> { };

// Making a reference to the type. This should only appear on the
// parser stage
struct TypeRef : public types::Type, public Base {
  std::vector<TypeRef*> generics;

  /// @brief Internal type when using @fn types::Type::toRef().
  /// @note this shoudn't be used for normal usage!
  types::Type* internalType = nullptr;

  /// @brief AST used to declare this TypeRef.
  /// @note this shoudn't be used for normal usage!
  Expression::Base* internalAST = nullptr;

  /// @brief The id of the type
  std::string id;

 public:
  TypeRef(std::string p_name, DBGSourceInfo* p_dbg, std::vector<TypeRef*> p_generics = {}, std::string id = "");
  TypeRef(std::string p_name, DBGSourceInfo* p_dbg, types::Type* internalType, std::string id);
  TypeRef(Expression::Base* p_ast, std::string p_name, DBGSourceInfo* p_dbg, std::string id);

  /// @brief Get type's generics
  std::vector<TypeRef*> getGenerics();
  /// @return A good looking, human readable representation of
  ///  this type.
  std::string getPrettyName() const override;
  /// @brief Set a generic list for this type
  void setGenerics(std::vector<TypeRef*> g);

  /// @return Internal type when using @fn types::Type::toRef().
  /// @note this shoudn't be used for normal usage!
  auto _getInternalType() { return internalType; }

  /// @return AST used to declare this TypeRef.
  /// @note this shoudn't be used for normal usage!
  auto _getInternalAST() { return internalAST; }

  /// @return true if it's a delctype(...)
  virtual bool isTypeDecl() { return false; }
  /// @return true if the type is a pointer
  virtual bool isReferenceType() { return false; }
  /// @return true if the type is a pointer
  virtual bool isPointerType() { return false; }
  /// @return true if the type is a function
  virtual bool isFunctionType() { return false; }

  /// @return The id of the type
  auto getId() { return id; }

  ACCEPT()
  ~TypeRef() noexcept = default;
};

/**
 * @class DeclType
 * @brief A struct representing a declaration type that derives from
 * TypeRef.
 *
 * This struct holds a pointer to a Base object and provides methods
 * to access the expression value and determine if it is a type
 * declaration.
 */
struct DeclType : public TypeRef {
  Base* value;

 public:
  DeclType(Base* value, DBGSourceInfo* srcInfo);

  /// @return the expr value to get the type from
  auto getExpr() { return value; }
  bool isTypeDecl() override { return true; }

  ~DeclType() noexcept = default;
};

/**
 * @class FuncType
 * @brief A struct representing a function type that derives from
 * TypeRef.
 *
 * This struct holds a pointer to a TypeRef object and provides methods
 * to access the type value and determine if it is a function type.
 */
struct FuncType : public TypeRef {
  /// @brief The return value of the function
  TypeRef* returnValue;
  /// @brief The arguments of the function
  std::vector<TypeRef*> args;

 public:
  FuncType(std::vector<TypeRef*> args, TypeRef* returnValue, DBGSourceInfo* srcInfo);

  /// @return the arguments of the function
  auto getArgs() { return args; }
  /// @return the return value of the function
  auto getReturnValue() { return returnValue; }

  bool isFunctionType() override { return true; }

  ~FuncType() noexcept = default;
};

/**
 * @class TupleType
 * @brief A struct representing a tuple type that derives from
 * TypeRef.
 *
 * This struct holds a pointer to a TypeRef object and provides methods
 * to access the type value and determine if it is a tuple type.
 */
struct TupleType : public TypeRef {
  std::vector<TypeRef*> types;

 public:
  TupleType(std::vector<TypeRef*> types, DBGSourceInfo* srcInfo);

  /// @return the arguments of the function
  auto getTypes() { return types; }

  ~TupleType() noexcept = default;
};

/**
 * @class ReferenceType
 * @brief A struct representing a pointer type that derives from
 * TypeRef.
 *
 * This struct holds a pointer to a TypeRef object and provides methods
 * to access the type value and determine if it is a pointer type.
 */
struct ReferenceType : public TypeRef {
  TypeRef* baseType;

 public:
  ReferenceType(TypeRef* baseType, DBGSourceInfo* srcInfo);

  /// @return the expr value to get the type from
  auto getBaseType() { return baseType; }
  bool isReferenceType() override { return true; }

  ~ReferenceType() noexcept = default;
};

/**
 * @class PointerType
 * @brief A struct representing a pointer type that derives from
 * TypeRef.
 *
 * This struct holds a pointer to a TypeRef object and provides methods
 * to access the type value and determine if it is a pointer type.
 */
struct PointerType : public TypeRef {
  TypeRef* baseType;

 public:
  PointerType(TypeRef* baseType, bool isMutable, DBGSourceInfo* srcInfo);

  /// @return the expr value to get the type from
  auto getBaseType() { return baseType; }
  bool isPointerType() override { return true; }

  ~PointerType() noexcept = default;
};

/**
 * @brief Represents a "where" clause in a program.
 *
 * The `WhereClause` struct is used to define constraints or conditions
 * in a program. It is typically used in conjunction with templates or
 * generic programming to restrict the types that can be used as arguments.
 *
 * @code rs
 *  fn example<T: Sized + IsPointer>() { ... }
 *                ^^^^^^^^^^^^^^^^^ 2 checks
 * @endcode
 */
struct WhereClause {
 public:
  using ChecksVectorType = std::vector<TypeRef*>;

 private:
  /**
   * @brief A vector containing the checks that should be executed
   *  for each generic argument.
   */
  ChecksVectorType checks;

 public:
  WhereClause(ChecksVectorType checks) : checks(checks) { }
  explicit WhereClause(TypeRef* check) : checks(ChecksVectorType{check}) { }

  /// @return The checks to perform
  auto getChecks() { return checks; }

  ~WhereClause() = default;
};

/// Function signature parameter helper node (name: type).
struct Param {
  // Parameter's name.
  std::string name;

  // Parameter's type. Note, if the prarameter
  // type is "Generic", `type` actually refers
  // to the default generic parameter.
  TypeRef* type = nullptr;
  /// @brief default value used for the function
  Syntax::Expression::Base* defaultValue = nullptr;
  /// @brief The where clause for the parameter-
  /// @note This only should be for generic parameters!
  WhereClause* whereClause = nullptr;
  /// @brief Parameter status (aka: parameter type)
  enum Status {
    Normal,
    Generic
  } status;
  /// @brief If the argument is mutable or not
  bool mutableArg = false;

 public:
  /// @brief Create a new param instance
  explicit Param(std::string name = "", TypeRef* type = nullptr, Status generic = Normal);

  /// Get the param status, whether
  /// it is a generic parameter or a normal one
  auto getStatus() { return status; }
  /// @return The parameter's type
  TypeRef* getType() const { return type; };
  /// @brief Set parameter's type
  void setType(TypeRef* ty) { type = ty; };
  /// @brief Set the default value to the parameter
  void setDefaultValue(Base* b) { defaultValue = b; }
  /// @brief Parameter's name
  std::string getName() const { return name; };
  /// @brief check if the function contains a default value
  bool hasDefaultValue() { return defaultValue != nullptr; }
  /// @return default value if it exists
  auto getDefaultValue() {
    assert(status == Normal);
    assert(hasDefaultValue());
    return defaultValue;
  }
  /// @return The where clause for this generic parameter
  auto getWhereClause() const {
    assert(status == Generic);
    return whereClause;
  };
  /// @brief Set The where clause for this generic parameter
  void setWhereClause(WhereClause* clause) {
    assert(status == Generic);
    whereClause = clause;
  };
  /// @brief Set the parameter's mutability
  void setMutable(bool m = true) { mutableArg = m; }
  /// @brief If the variable is mutable or not
  bool isMutable() { return mutableArg; }
};
} // namespace Expression

namespace Statement {

/**
 * This struct is used a sort of container
 * for any node that require generic
 * expressions.
 *
 * e.g. Functions, classes, etc...
 */
template <typename T = Expression::Param*>
struct GenericContainer {
  using GenericList = std::vector<T>;
  GenericList generics;

  bool _generic = false;

 public:
  GenericContainer() = default;
  GenericContainer(GenericList generics) : _generic(true), generics(generics) {};

  GenericList getGenerics() const { return generics; }
  void setGenerics(GenericList list) {
    _generic = true;
    generics = std::move(list);
  }

  /// @return iterator to the first generic
  auto genericsBegin() { return generics.begin(); }
  /// @return iterator beyond the last generic
  auto genericsEnd() { return generics.end(); }
  /// @return true if the node has generics
  bool isGeneric() { return _generic; }
};
} // namespace Statement

} // namespace Syntax
} // namespace snowball

#endif // __SNOWBALL_AST_COMMON_NODES_H_
