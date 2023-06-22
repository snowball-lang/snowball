

#include "../errors/error.h"
#include "../types/PrimitiveTypes.h"

#include <deque>
#include <functional>
#include <list>
#include <map>
#include <memory>
#include <optional>
#include <string>
#include <vector>

#ifndef __SNOWBALL_AST_CONTEXT_H_
#define __SNOWBALL_AST_CONTEXT_H_

namespace snowball
{
namespace Syntax
{

template <typename T>
class ASTContext {
    using Item = std::shared_ptr<T>;
    using Scope = std::map<std::string, Item>;

  protected:
    /** A scope is a representation of a "block" where all
     * the variables are stored into it. Variables can be
     * accessed from parent scopes and the order of finding
     * them is from start to end.
     *
     *   fn ...() {
     *     var a = 2;
     *
     *     if (a == 2) {
     *        a = 3
     *     }
     *   }
     *
     * This would be equal to the following stack:
     *   if-stmt scope > fn scope > global scope
     *      (no vars)     (var a)   (types, etc)
     */
    std::shared_ptr<std::deque<Scope>> stack = std::make_shared<std::deque<Scope>>();

  public:
    ASTContext() {
        // Create a global scope for primitive types
        addScope();
    }

    ~ASTContext() noexcept = default;

    /**
     * @brief Insert an item into the current stack
     *
     * @param name Identifier for the item
     * @param item Item to be stored
     */
    virtual void
    addItem(const std::string& name, Item& item) {
        DEBUG_SYMTABLE(1, FMT("    Adding to scope: %s", name.c_str()).c_str())
        auto f = stack->front();
        auto val = f.find(name);

        if (val != f.end()) {
            E<VARIABLE_ERROR>(item,
                              FMT("Value for '%s' is already defiend!", item->toString().c_str()));
        }

        stack->front().emplace(std::make_pair(name, item));
    }

    /**
     * @brief Get the Item from the stack
     *
     * @param name  Item to search for
     * @return {item or nullptr, if found}
     */
    virtual std::pair<Item, bool>
    getItem(const std::string name) const {
        for (auto s : *stack) {
            auto [val, found] = getInScope(name, s);
            if (found) return {val, true};
        }

        return {std::unique_ptr<T>(nullptr), false};
    }

    /**
     * @brief Search for an item in a certain scope
     *
     * @param name item to search for
     * @param s scope where search is performed
     * @return {item or nullptr, if found}
     */
    virtual std::pair<Item, bool>
    getInScope(const std::string name, Scope& s) const {
        auto val = s.find(name);
        if (val != s.end()) {
            return {val->second, true};
        }

        return {std::unique_ptr<T>(nullptr), false};
    }
    /// @return the current scope the programm is into
    virtual Scope&
    currentScope() {
        return stack->front();
    }
    /// @return the global scope
    virtual Scope&
    globalScope() {
        return stack->at(stack->size() - 2);
    }
    /// @brief Create a new scope and append it.
    virtual void
    addScope() {
        DEBUG_SYMTABLE(0, "Creating new scope")

        Scope newScope{};
        stack->insert(stack->begin(), newScope);
    }
    /// @brief Run a function inside a scope
    virtual Scope
    withScope(std::function<void()> func) {
        addScope();
        func();

        return delScope();
    }
    /**
     * @brief Delete the current scope
     * @return Scope The deleted scope
     */
    virtual Scope
    delScope() {
        DEBUG_SYMTABLE(0, "Deleting scope")

        auto s = stack->front();
        stack->pop_front();

        return s;
    }
};

} // namespace Syntax
} // namespace snowball

#endif // __SNOWBALL_AST_CONTEXT_H_
