
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

class ReferenceType : public AcceptorExtend<ReferenceType, Type>, public DBGObject, public ir::IdMixin {
    friend AcceptorExtend;

  private:
    /// @brief Base class that this type is pointing to
    std::shared_ptr<Type> base = nullptr;

  public:
    ReferenceType(std::shared_ptr<Type> base);
    ReferenceType(const ReferenceType& other) = default;

    /**
     * @param other another type to check.
     */
    virtual bool is(Type* other) const override {
        if (auto c = utils::cast<ReferenceType>(other)) { return base->is(c->getPointedType()); }

        return false;
    }

    /// @brief Get the type represented as a "human-readable" string
    std::string getPrettyName() const override;
    /// @return the mangled version of the type
    std::string getMangledName() const override;
    /// @return The pointed type this type is pointing to
    /// @see ReferenceType::base
    std::shared_ptr<Type> getPointedType() const;
    /// @return The base type being pointed.
    /// @example i32**** -> i32
    std::shared_ptr<Type> getBaseType() const;

    /// @c Type::toRef() for information about this function.
    /// @note It essentially does the same thing except it adds
    ///  generics if needed
    Syntax::Expression::TypeRef* toRef() override;

    SNOWBALL_TYPE_CLONE(ReferenceType)

    /// @brief override function. All numeric types
    ///  can cast to any other numeric types.
    bool canCast(Type* ty) const override;

    template <class Down>
    std::shared_ptr<Down> downcasted_shared_from_this() {
        return std::dynamic_pointer_cast<Down>(Type::shared_from_this());
    }
};

}; // namespace types
}; // namespace snowball

#endif // __SNOWBALL_AST_POINTER_TYPES_H_
