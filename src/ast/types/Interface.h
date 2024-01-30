
#include "../../common.h"
#include "../../constants.h"
#include "../../ir/id.h"
#include "../../ir/module/Module.h"
#include "../../utils/utils.h"
#include "../syntax/common.h"
#include "../syntax/nodes.h"
#include "BaseType.h"
#include "DefinedType.h"
#include "Type.h"

#include <memory>
#include <string>
#include <vector>

#include "../syntax/nodes.h"

#ifndef __SNOWBALL_AST_INTERFACES_TYPES_H_
#define __SNOWBALL_AST_INTERFACES_TYPES_H_

namespace snowball {
namespace types {

/**
 * @brief Interface types.
 *
 * These can also be called as classes or objects. This
 * type is defined by the programmer. It can contain some extra
 * stuff such as generics and it's own defined members. Unlike
 * primitive types, in order to use these type and it's member,
 * a new initialization of the object is required.
 *
 * @note This type is different from the DefinedType type.
 * The difference is that this type is used for interfaces
 * and the DefinedType is used for classes.
 *
 * @see DefinedType
 */
class InterfaceType : public BaseType {
 public:
  struct Member : public DefinedType::ClassField {
    enum Kind {
      FIELD,
      METHOD
    } kind;

    explicit Member(
    const std::string& name,
    Type* type,
    Kind kind,
    Syntax::Statement::Base* ast,
    Privacy privacy = PRIVATE,
    bool isMutable = false
    )
      : ClassField(name, type, privacy, nullptr, isMutable), kind(kind), ast(ast) {};
    Syntax::Statement::Base* ast;
  };

 private:
  /// @brief a list of fields this class has
  std::vector<Member*> fields;

 public:
  InterfaceType(
  const std::string& name,
  const std::string uuid,
  std::shared_ptr<ir::Module> module,
  std::vector<Member*> fields = {},
  std::vector<Type*> generics = {}
  )
    : BaseType(INTERFACE, name), fields(fields) {
    setGenerics(generics);
    unsafeSetUUID(uuid);
    unsafeSetModule(module);
  };
  InterfaceType(const InterfaceType&) = default;
  InterfaceType& operator=(InterfaceType const&) = delete;
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
    if (auto c = utils::cast<InterfaceType>(other)) { return is(c); }
    return false;
  }

  /**
   * @brief Check whether one defiend type equals
   *  another defined type.
   *
   * @param other Type to check
   * @return true/false depending on the equality
   */
  virtual bool is(InterfaceType* other) const;

  /// @brief Get the type represented as a "human-readable" string
  std::string getPrettyName() const override;
  /// @return the mangled version of the type
  std::string getMangledName() const override;
  /// @return A list containing all the fields declared for the interface
  /// @note It does not include the parent fields!
  auto getFields() const { return fields; }
  /// @brief Add a new field to the interface
  void addField(Member* f) { fields.emplace_back(f); }
  /// @c Type::toRef() for information about this function.
  /// @note It essentially does the same thing except it adds
  ///  generics if needed
  Syntax::Expression::TypeRef* toRef() override;

  /// @brief override function.
  virtual bool canCast(Type* ty) const override { return false; }
  virtual bool canCast(InterfaceType* ty) const { return false; }

 public:
  virtual std::int64_t sizeOf() const override;
  virtual std::int64_t alignmentOf() const override;

  SNOWBALL_TYPE_COPIABLE(InterfaceType)
};

}; // namespace types
}; // namespace snowball

#endif // __SNOWBALL_AST_INTERFACES_TYPES_H_
