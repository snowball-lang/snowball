
#include "../../common.h"
#include "../../constants.h"
#include "../../ir/id.h"
#include "../../ir/module/Module.h"
#include "../../utils/utils.h"
#include "../syntax/common.h"
#include "../syntax/nodes.h"
#include "Type.h"

#include <memory>
#include <string>
#include <vector>

#ifndef __SNOWBALL_AST_POINTER_TYPES_H_
#define __SNOWBALL_AST_POINTER_TYPES_H_

namespace snowball {
namespace types {

class FunctionType;

class PointerType : public AcceptorExtend<PointerType, Type>,
                    public ir::IdMixin,
                    public DBGObject,
                    public std::enable_shared_from_this<PointerType> {
    friend AcceptorExtend;

  private:
    /// @brief Base class that this type is pointing to
    std::shared_ptr<Type> base = nullptr;

  public:
    PointerType(std::shared_ptr<Type> base);

    /**
     * @param other another type to check.
     */
    virtual bool is(Type *other) override {
        if (auto c = utils::cast<PointerType>(other)) {
            return base->is(c->getPointedType());
        }

        return false;
    }

    /// @brief Get the type represented as a "human-readable" string
    std::string getPrettyName() const override;
    /// @return the mangled version of the type
    std::string getMangledName() const override;
    /// @return The pointed type this type is pointing to
    /// @see PointerType::base
    std::shared_ptr<Type> getPointedType() const;

    /// @c Type::toRef() for information about this function.
    /// @note It essentially does the same thing except it adds
    ///  generics if needed
    Syntax::Expression::TypeRef *toRef() override;

    /// @brief override function. All numeric types
    ///  can cast to any other numeric types.
    bool canCast(Type *ty) override;
};

}; // namespace types
}; // namespace snowball

#endif // __SNOWBALL_AST_POINTER_TYPES_H_
