
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
class DefinedType : public AcceptorExtend<DefinedType, Type>,
                    public ir::IdMixin {
  public:
    /**
     * @brief A class field represents all of the "elements" a
     *  type has stored into it.
     *
     * @note The number of items does not affect whether this type
     *  is eqaul to another type.
     */
    struct ClassField : public Syntax::Statement::Privacy {
        explicit ClassField(const std::string& name, std::shared_ptr<Type> type,
                            Privacy privacy = PRIVATE);

        const std::string name;
        const std::shared_ptr<Type> type;
    };

    friend AcceptorExtend;

  private:
    /// @brief A list containing the already-generated generics
    ///  for this class
    std::vector<std::shared_ptr<Type>> generics;
    /// @brief a list of fields this class has
    std::vector<ptr<ClassField>> fields;
    /// @brief Definition of where in the stack this class is stored
    /// @example [module name].MyClass:2
    std::string uuid;
    /// @brief A module where the type is defined.
    std::shared_ptr<ir::Module> module;

  public:
    DefinedType(const std::string& name, const std::string uuid,
                std::shared_ptr<ir::Module> module,
                std::vector<ptr<ClassField>> fields         = {},
                std::vector<std::shared_ptr<Type>> generics = {});

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
    virtual bool is(ptr<Type> other) override {
        if (auto f = utils::cast<DefinedType>(other)) {
            return is(f);
        }

        return false;
    }

    /**
     * @brief Check whether one defiend type equals
     *  another defined type.
     *
     * @param other Type to check
     * @return true/false depending on the equality
     */
    virtual bool is(ptr<DefinedType> other);

    /// @return module where the type is defined in
    std::shared_ptr<ir::Module> getModule() const;
    /// @brief Get the type represented as a "human-readable" string
    std::string getPrettyName() const override;
    /// @return the mangled version of the type
    std::string getMangledName() const override;
    /// @return UUID of the class that can be used as UUID base
    std::string getUUID() const;
    /// @return the generic list defined for this type
    auto getGenerics() const { return generics; }

    /// @c Type::toRef() for information about this function.
    /// @note It essentially does the same thing except it adds
    ///  generics if needed
    ptr<Syntax::Expression::TypeRef> toRef() override;
};

};     // namespace types
};     // namespace snowball

#endif // __SNOWBALL_AST_DEFINED_TYPES_H_