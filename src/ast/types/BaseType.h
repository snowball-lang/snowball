
#include "../../common.h"
#include "../../DBGSourceInfo.h"
#include "../../ast/syntax/nodes.h"
#include "../../ast/syntax/common.h"
#include "../../ir/id.h"
#include "../../ir/module/Module.h"
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
                public Syntax::Statement::GenericContainer<std::shared_ptr<Type>>,
                public ir::IdMixin {
  protected:
    /// @brief Definition of where in the stack this class is stored
    /// @example [module name].MyClass:2
    std::string uuid;
    /// @brief A module where the type is defined.
    std::shared_ptr<ir::Module> module;

  public:
    BaseType(Kind kind, const std::string name);

    /// @brief Get the module where the type is defined.
    std::shared_ptr<ir::Module> getModule() const;
    /// @brief Get the UUID of the type.
    std::string getUUID() const;

    /// @brief Set the module where the type is defined.
    void setModule(std::shared_ptr<ir::Module> m);
    /// @brief Set the UUID of the type.
    void setUUID(const std::string uuid);

    template <class Down>
    std::shared_ptr<Down> downcasted_shared_from_this() {
        return std::dynamic_pointer_cast<Down>(Type::shared_from_this());
    }
};

}; // namespace types
}; // namespace snowball

#endif // __SNOWBALL_AST_BASE_TYPE_H_
