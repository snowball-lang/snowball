
#include "../DBGSourceInfo.h"
#include "../ast/types/Type.h"
#include "../ir/values/Func.h"
#include "../ir/values/Value.h"

#include <deque>
#include <iomanip>

#ifndef __SNOWBALL_TRANSFORM_ITEM_H_
#define __SNOWBALL_TRANSFORM_ITEM_H_

namespace snowball {
namespace Syntax {
namespace transform {

// TransfiormItem is the value stored/fetched
// from the stack. It can either represent a
// value, a function or a type.
class Item : public DBGObject {
    // Using a type definition incase we need to
    // change it.
    using ValuePtr = std::shared_ptr<ir::Value>;
    using FunctionPtr = std::shared_ptr<ir::Func>;
    using TypePtr = std::shared_ptr<types::Type>;

    // This value is the actual value gotten from
    // the stack.
    ValuePtr value = nullptr;
    // The value stored that represents a type in
    // TypePtr IR.
    TypePtr tyVal = nullptr;
    // Module stored inside this item. The module can
    // be either user-defined or it can be imported from
    // another file.
    std::shared_ptr<ir::Module> module = nullptr;
    /**
     * Function items are a bit different. Since functions
     * can have the same name but different arguments types,
     * we would need something to do in order to fix any
     * conflicts between multiple functions on the stack.
     *
     * The solution to this was to store all the "generated"
     * functions stored into a single Item, acting like a sort
     * of cache.
     *
     * @note Functions stored in here where already generated from
     *  before meaning that it will not contain any generics
     * information.
     *
     * Another problem we encountered with function overloading is
     * that if we opted by storing them into the stack as single
     * items, the only way so that we can make them unique would be
     * by storing functions with it's mangled verion acting as
     * identifier.
     *
     * This would be a very bad life decition since we will need to
     * mangled functions that hasn't been generated yet, creating a
     * whole new world where bugs and errors can be stored.
     *
     * @example
     *   fn hello(i32)
     *   fn hello(f64)
     *   ---------- stored as: ------------
     *   Item<type: FUNC>:
     *     - functions: [fn void(i32), fn void(f64)]
     *   -------- stored in stack: --------
     *   Stack:
     *      "hello": Item<type: FUNC> ---^
     */
    std::deque<FunctionPtr> functions;

  public:
    // The type used to represent what this
    // item holds as value.
    enum Type
    {
        TYPE,
        FUNC,
        VALUE,
        MODULE
    } type;

    // Constructors and destructors for the
    // item.
    ~Item() noexcept = default;

    Item(Type type, ValuePtr val) : type(type), value(val){};
    Item(FunctionPtr fn) : type(FUNC), functions({fn}){};
    Item(std::shared_ptr<ir::Module> m) : module(m), type(MODULE){};
    Item(TypePtr val) : type(TYPE), tyVal(val){};

    // Utility functions to identify the item
    bool isType() { return type == TYPE; }
    bool isFunc() { return type == FUNC; }
    bool isVal() { return type == VALUE; }
    bool isModule() { return type == MODULE; }

    /// @return The module stored inside this item
    auto getModule() const {
        assert(type == MODULE);
        return module;
    }
    /// @return The value stored inside this item
    auto getValue() const {
        assert(type == VALUE);
        return value;
    }
    /// @return The type being represented as an item on the stack.
    auto getType() const {
        assert(type == TYPE);
        return tyVal;
    }

    /// @return a full list of functions stored in this item
    auto& getFunctions() {
        assert(type == FUNC);
        return functions;
    }
    /// @brief append a new function pointer to this item.
    void addFunction(FunctionPtr fn) {
        assert(type == FUNC);
        functions.push_front(fn);
    }

    std::string toString() { /*TODO:*/
        assert(false);
        return "<TODO: transform item name>";
    };
};

} // namespace transform
} // namespace Syntax
} // namespace snowball

#endif // __SNOWBALL_TRANSFORM_ITEM_H_