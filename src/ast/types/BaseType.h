
#include "../../ast/syntax/common.h"
#include "../../ast/syntax/nodes.h"
#include "../../common.h"
#include "../../ir/id.h"
#include "../../ir/module/Module.h"
#include "../../sourceInfo/DBGSourceInfo.h"
#include "Type.h"

#include <memory>
#include <string>

#ifndef __SNOWBALL_AST_BASE_TYPE_H_
#define __SNOWBALL_AST_BASE_TYPE_H_

namespace snowball {

namespace Syntax {
namespace Expression {
class TypeRef;
}
}; // namespace Syntax

namespace types {

class BaseType : public Type,
                 public DBGObject,
                 public Syntax::Statement::Privacy,
                 public Syntax::Statement::GenericContainer<Type*>,
                 public ir::IdMixin {
 protected:
  /// @brief Definition of where in the stack this class is stored
  /// @example [module name].MyClass:2
  std::string uuid;
  /// @brief A module where the type is defined.
  std::shared_ptr<ir::Module> module;

 public:
  BaseType(Kind kind, const std::string name);
  BaseType(const BaseType& other) = default;

  /// @brief Get the module where the type is defined.
  std::shared_ptr<ir::Module> getModule() const;
  /// @brief Get the UUID of the type.
  std::string getUUID() const;

  /// @brief Set the module where the type is defined.
  void unsafeSetModule(std::shared_ptr<ir::Module> m);
  /// @brief Set the UUID of the type.
  void unsafeSetUUID(const std::string uuid);

  virtual std::int64_t sizeOf() const override { assert(false); }
  virtual std::int64_t alignmentOf() const override { assert(false); }

  SNOWBALL_TYPE_COPIABLE(BaseType)
};

}; // namespace types
}; // namespace snowball

#endif // __SNOWBALL_AST_BASE_TYPE_H_
