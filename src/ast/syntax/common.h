

#include "../../DBGSourceInfo.h"
#include "../../common.h"

#include <assert.h>
#include <string>
#include <vector>

#ifndef __SNOWBALL_AST_COMMON_NODES_H_
#define __SNOWBALL_AST_COMMON_NODES_H_

#include "../types/Type.h"
#define ACCEPT() void accept(Syntax::Visitor *v) override;

namespace snowball {

namespace Attributes {
enum Fn {
    LLVM_FUNC,
    INTERNAL_LINKAGE,
};
}

namespace Syntax {
class Visitor;

struct Node : public DBGObject {
  public:
    Node()           = default;
    ~Node() noexcept = default;

    virtual void accept(Syntax::Visitor *v) = 0;

    /// @brief A flag that tells if the current node is
    ///  an operator
    bool isOperator = false;
};

/**
 * @brief This namespaces are used just for the more "generic"
 *  classes that can be inherited to make my life easier.
 */

namespace Expression {
struct Base : public AcceptorExtend<Base, Node> {
    using AcceptorExtend::AcceptorExtend;
    void accept(Syntax::Visitor *v) override { assert(false); };
};

// Making a reference to the type. This should only appear on the
// parser stage
struct TypeRef : public types::Type, public Base {
    std::vector<TypeRef *> generics;

    /// @brief Internal type when using @fn types::Type::toRef().
    /// @note this shoudn't be used for normal usage!
    std::shared_ptr<types::Type> internalType = nullptr;

    /// @brief AST used to declare this TypeRef.
    /// @note this shoudn't be used for normal usage!
    Expression::Base *internalAST = nullptr;

  public:
    TypeRef(std::string p_name, DBGSourceInfo *p_dbg,
            std::vector<TypeRef *> p_generics = {});
    TypeRef(std::string p_name, DBGSourceInfo *p_dbg,
            std::shared_ptr<types::Type> internalType);
    TypeRef(Expression::Base *p_ast, std::string p_name, DBGSourceInfo *p_dbg);

    /// @brief Get type's generics
    std::vector<TypeRef *> getGenerics();
    /// @return A good looking, human readable representation of
    ///  this type.
    std::string getPrettyName() const override;
    /// @brief Set a generic list for this type
    void setGenerics(std::vector<TypeRef *> g);

    /// @return Internal type when using @fn types::Type::toRef().
    /// @note this shoudn't be used for normal usage!
    auto _getInternalType() { return internalType; }

    /// @return AST used to declare this TypeRef.
    /// @note this shoudn't be used for normal usage!
    auto _getInternalAST() { return internalAST; }

    /// @return true if it's a delctype(...)
    virtual bool isTypeDecl() { return false; }

    ACCEPT()
    ~TypeRef() noexcept = default;
};

struct DeclType : public TypeRef {
    Base *value;

  public:
    DeclType(Base *value, DBGSourceInfo *srcInfo);

    /// @return the expr value to get the type from
    auto getExpr() { return value; }

    bool isTypeDecl() override { return true; }
    ~DeclType() noexcept = default;
};

/// Function signature parameter helper node (name: type).
struct Param {

    // Parameter's name.
    std::string name;

    // Parameter's type. Note, if the prarameter
    // type is "Generic", `type` actually refers
    // to the default generic parameter.
    TypeRef *type = nullptr;
    /// @brief default value used for the function
    Syntax::Expression::Base *defaultValue = nullptr;

    enum Status { Normal, Generic } status;

  public:
    /// @brief Create a new param instance
    explicit Param(std::string name = "", TypeRef *type = nullptr,
                   Status generic = Normal);

    /// Get the param status, whether
    /// it is a generic parameter or a normal one
    auto getStatus() { return status; }

    /// @brief Get parameter's type
    TypeRef *getType() const { return type; };
    /// @brief Set the default value to the parameter
    void setDefaultValue(Base *b) { defaultValue = b; }

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
};
} // namespace Expression

namespace Statement {

/**
 * A generic class that accepts an enum as a template parameter and stores and
 *  checks attributes for a node.
 *
 * @tparam T The enum type representing the attributes that can be stored.
 */
template <typename T> class AttributeHolder {
  public:
    /**
     * Checks if a specific attribute is set for the node.
     *
     * @param attribute The attribute to check.
     * @return True if the attribute is set, false otherwise.
     */
    bool hasAttribute(T attribute) const {
        return (m_attributes & (1 << static_cast<int>(attribute))) != 0;
    }
    /**
     * Sets the bit for a specific attribute in the `m_attributes` variable.
     *
     * @param attribute The attribute to add.
     */
    auto addAttribute(T attribute) {
        return m_attributes |= (1 << static_cast<int>(attribute));
    }
    /**
     * Sets a new list of attributes to the current holder
     */
    void setAttributes(unsigned int attribute) { m_attributes = attribute; }
    /**
     * Returns the respective unsigned integer for the attributes
     */
    auto getAttributes() const { return m_attributes; }
    /**
     * Clears the bit for a specific attribute in the `m_attributes` variable.
     *
     * @param attribute The attribute to remove.
     */
    void removeAttribute(T attribute) {
        m_attributes &= ~(1 << static_cast<int>(attribute));
    }
    /**
     * Clears all attributes for the node by setting `m_attributes` to zero.
     */
    void clearAttributes() { m_attributes = 0; }

  private:
    /** The bit field storing the attributes for the node. */
    unsigned int m_attributes = 0;
};

/**
 * This struct is used a sort of container
 * for any node that require generic
 * expressions.
 *
 * e.g. Functions, classes, etc...
 */
template <typename T = Expression::Param *> struct GenericContainer {

    using GenericList = std::vector<T>;
    GenericList generics;

  public:
    GenericContainer(){};
    GenericContainer(GenericList generics) : generics(generics){};

    GenericList getGenerics() const { return generics; }
    void setGenerics(GenericList list) { generics = std::move(list); }

    /// @return iterator to the first generic
    auto genericsBegin() { return generics.begin(); }
    /// @return iterator beyond the last generic
    auto genericsEnd() { return generics.end(); }
};
} // namespace Statement

} // namespace Syntax
} // namespace snowball

#endif // __SNOWBALL_AST_COMMON_NODES_H_
