
#include "../../common.h"
#include "../../constants.h"
#include "../../ir/id.h"
#include "../../ir/module/Module.h"
#include "../../utils/utils.h"
#include "../syntax/common.h"
#include "../syntax/nodes.h"
#include "BaseType.h"
#include "Type.h"

#include <memory>
#include <string>
#include <vector>

#ifndef __SNOWBALL_AST_DEFINED_TYPES_H_
#define __SNOWBALL_AST_DEFINED_TYPES_H_

namespace snowball {
namespace types {

/**
 * @brief Defined types.
 *
 * These can also be called as classes or objects. This
 * type is defined by the programmer. It can contain some extra
 * stuff such as generics and it's own defined members. Unlike
 * primitive types, in order to use these type and it's member,
 * a new initialization of the object is required.
 */
class DefinedType : public AcceptorExtend<DefinedType, BaseType> {
 public:
  /**
   * @brief A class field represents all of the "elements" a
   *  type has stored into it.
   *
   * @note The number of items does not affect whether this type
   *  is eqaul to another type.
   */
  struct ClassField : public Syntax::Statement::Privacy, public DBGObject {
    explicit ClassField(
      const std::string& name,
      Type* type,
      Privacy privacy = PRIVATE,
      Syntax::Expression::Base* initializedValue = nullptr,
      bool isMutable = false
    );
    const std::string name;
    Type* type;

    Syntax::Expression::Base* initializedValue = nullptr;

    bool isMutable = false;
    bool initialized = false;
  };

  friend AcceptorExtend;

 private:
  /// @brief a list of fields this class has
  std::vector<ClassField*> fields;
  /// @brief a list of static fields this class has
  std::vector<std::shared_ptr<ir::VariableDeclaration>> staticFields;
  /// @brief Parent class where the class in inherited from
  DefinedType* parent = nullptr;
  /// @brief The ast representation for the type
  Syntax::Statement::DefinedTypeDef* ast = nullptr;
  /// @brief Whether or not the type is a struct
  bool _struct = false;

 public:
  DefinedType(
    const std::string& name,
    const std::string uuid,
    std::shared_ptr<ir::Module> module,
    Syntax::Statement::DefinedTypeDef* ast = nullptr,
    std::vector<ClassField*> fields = {},
    std::vector<std::shared_ptr<ir::VariableDeclaration>> staticFields = {},
    DefinedType* parent = nullptr,
    std::vector<Type*> generics = {},
    bool isStruct = false
  );
  DefinedType(const DefinedType&) = default;
  DefinedType& operator=(DefinedType const&) = delete;
  /**
   * @param other another type to check.
   *
   * @note Class types will only be checked
   *  if the @param other is also a defined type.
   *
   *  For other types such as: function types and
   *  primitive types, this function will automatically
   *  return false.
   */
  virtual bool is(Type* other) const override {
    if (auto c = utils::cast<DefinedType>(other)) { return is(c); }
    return false;
  }

  /**
   * @brief Check whether one defiend type equals
   *  another defined type.
   *
   * @param other Type to check
   * @return true/false depending on the equality
   */
  virtual bool is(DefinedType* other) const;

  /// @brief Get the type represented as a "human-readable" string
  std::string getPrettyName() const override;
  /// @return the mangled version of the type
  std::string getMangledName() const override;
  /// @return The ast representation for the type
  Syntax::Statement::DefinedTypeDef* getAST() const;
  /// @return the parent class it inherits from
  /// @note It may be std::nullptr if it does not inherit from
  ///  anything!
  auto getParent() const { return parent; }
  /// @brief Set the parent class it inherits from
  void setParent(DefinedType* p) { parent = p; }
  /// @return true/false depending on whether the class has a parent
  auto hasParent() const { return parent != nullptr; }
  /// @return A list containing all the fields declared for the class
  /// @note It does not include the parent fields!
  auto& getFields() const { return fields; }
  /// @brief Append a new field (ClassField) to the list
  void addField(ClassField* f, bool toStart = false);
  /// @brief Set the fields for the class
  /// @note This should not be used unless you know what you are doing
  void setFields(std::vector<ClassField*> f) { fields = f; }
  /// @c Type::toRef() for information about this function.
  /// @note It essentially does the same thing except it adds
  ///  generics if needed
  Syntax::Expression::TypeRef* toRef() override;
  /// @return true/false depending on whether the type is a struct
  bool isStruct() const { return _struct; }

  /// @brief Get the static fields for the class
  auto& getStaticFields() const { return staticFields; }
  /// @brief Add a new static field to the class
  void addStaticField(std::shared_ptr<ir::VariableDeclaration> field) { staticFields.emplace_back(field); }

  void setMutable(bool m) override;

  /// @brief override function.
  virtual bool canCast(Type* ty) const override;
  virtual bool canCast(DefinedType* ty) const;

 public:
  /// @brief If the class has a constructor
  bool hasConstructor = false;

  virtual std::int64_t sizeOf() const override;
  virtual std::int64_t alignmentOf() const override;

  SNOWBALL_TYPE_COPIABLE(DefinedType)
};

}; // namespace types
}; // namespace snowball

#endif // __SNOWBALL_AST_DEFINED_TYPES_H_
