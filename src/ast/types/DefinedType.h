
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

class FunctionType;

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
                    public ir::IdMixin,
                    public DBGObject,
                    public std::enable_shared_from_this<DefinedType> {
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
                            Privacy privacy = PRIVATE, bool isMutable = false);

        const std::string name;
        const std::shared_ptr<Type> type;

        bool isMutable   = false;
        bool initialized = false;
    };

    friend AcceptorExtend;

  private:
    /// @brief A list containing the already-generated generics
    ///  for this class
    std::vector<std::shared_ptr<Type>> generics;
    /// @brief a list of fields this class has
    std::vector<ClassField *> fields;
    /// @brief Definition of where in the stack this class is stored
    /// @example [module name].MyClass:2
    std::string uuid;
    /// @brief A module where the type is defined.
    std::shared_ptr<ir::Module> module;
    /// @brief Parent class where the class in inherited from
    std::shared_ptr<DefinedType> parent = nullptr;
    /// @brief VTable holding all it's functions
    std::vector<std::shared_ptr<ir::Func>> classVtable;

  public:
    DefinedType(const std::string& name, const std::string uuid,
                std::shared_ptr<ir::Module> module,
                std::vector<ClassField *> fields            = {},
                std::shared_ptr<DefinedType> parent         = nullptr,
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
    virtual bool is(Type *other) override {
        if (auto c = utils::cast<DefinedType>(other)) {
            return is(c);
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
    virtual bool is(DefinedType *other);

    /// @return module where the type is defined in
    std::shared_ptr<ir::Module> getModule() const;
    /// @brief Get the type represented as a "human-readable" string
    std::string getPrettyName() const override;
    /// @return the mangled version of the type
    std::string getMangledName() const override;
    /// @return UUID of the class that can be used as UUID base
    std::string getUUID() const;
    /// @return The size of the class virtual table
    int getVtableSize();
    /// @brief Increase the size of the virtual table
    int addVtableItem(std::shared_ptr<ir::Func> f);
    /// @return a vector containing all the functions in a vtable
    std::vector<std::shared_ptr<ir::Func>> getVTable() const;
    /// @return the generic list defined for this type
    auto getGenerics() const { return generics; }
    /// @return the parent class it inherits from
    /// @note It may be std::nullptr if it does not inherit from
    ///  anything!
    auto getParent() const { return parent; }
    /// @return A list containing all the fields declared for the class
    /// @note It does not include the parent fields!
    auto getFields() const { return fields; }
    /// @brief Append a new field (ClassField) to the list
    void addField(ClassField *f);
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

#endif // __SNOWBALL_AST_DEFINED_TYPES_H_
