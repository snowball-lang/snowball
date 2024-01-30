
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

#ifndef __SNOWBALL_AST_ENUM_TYPES_H_
#define __SNOWBALL_AST_ENUM_TYPES_H_

namespace snowball {
namespace types {

/**
 * @brief Enum types.
 *
 * These types are defined by the programmer. They can contain some extra
 * stuff such as generics and it's own defined members. Unlike
 * primitive types, in order to use these type and it's member,
 * a new initialization of the object is required.
 */
class EnumType final : public AcceptorExtend<EnumType, BaseType> {
 public:
  /**
   * @brief An enum field represents all of the "elements" a
   * type has stored into it.
   *
   * @note The number of items does not affect whether this type
   * is eqaul to another type.
   */
  struct EnumField final : public DBGObject {
    explicit EnumField(
    const std::string& name,
    std::vector<types::Type*> types);

    const std::string name;
    std::vector<types::Type*> types;

    virtual ~EnumField() = default;
  };

  friend AcceptorExtend;

 private:
  /// @brief a list of fields this class has
  std::vector<EnumField> fields;

 public:
  EnumType(
  const std::string& name,
  const std::string uuid,
  std::shared_ptr<ir::Module> module,
  Privacy::Status privacy = PRIVATE
  );
  /**
   * @param other another type to check.
   *
   * @note Class types will only be checked
   *  if the @param other is also an enum type.
   *
   *  For other types such as: function types and
   *  primitive types, this function will automatically
   *  return false.
   */
  virtual bool is(Type* other) const override {
    if (auto c = utils::cast<EnumType>(other)) { return is(c); }
    return false;
  }

  /**
   * @brief Check whether one enum type equals
   *  another enum type.
   *
   * @param other Type to check
   * @return true/false depending on the equality
   */
  virtual bool is(EnumType* other) const;

  /// @brief Get the type represented as a "human-readable" string
  std::string getPrettyName() const override;
  /// @return the mangled version of the type
  std::string getMangledName() const override;
  /// @return A list containing all the fields declared for the class
  auto& getFields() const { return fields; }
  /// @brief Append a new field (EnumField) to the list
  void addField(EnumField f);
  /// @c Type::toRef() for information about this function.
  /// @note It essentially does the same thing except it adds
  ///  generics if needed
  Syntax::Expression::TypeRef* toRef() override;

  /// @brief override function.
  virtual bool canCast(Type* ty) const override;
  virtual bool canCast(EnumType* ty) const;

 public:

  virtual std::int64_t sizeOf() const override;
  virtual std::int64_t alignmentOf() const override;

  SNOWBALL_TYPE_COPIABLE(EnumType)
};

}; // namespace types
}; // namespace snowball

#endif // __SNOWBALL_AST_ENUM_TYPES_H_
