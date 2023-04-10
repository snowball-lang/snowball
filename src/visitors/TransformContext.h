
#include "../DBGSourceInfo.h"
#include "../ast/syntax/nodes.h"
#include "../ast/visitor/ASTContext.h"
#include "../ast/visitor/Visitor.h"
#include "../ir/values/Value.h"
#include "../services/ImportService.h"
#include "TransformItem.h"

#include <assert.h>
#include <string>
#include <vector>

#ifndef __SNOWBALL_TRANSFORM_CONTEXT_H_
#define __SNOWBALL_TRANSFORM_CONTEXT_H_

#include "../ast/cache/Cache.h"

namespace snowball {
namespace Syntax {

// This class gives context to the "Transformer" ast visitor
// and it also gives the ability to do stack management.
class TransformContext
    : public AcceptorExtend<TransformContext, ASTContext<transform::Item>> {
    // Current function being generated
    std::shared_ptr<ir::Func> currentFunction =
        std::shared_ptr<ir::Func>(nullptr);
    // Current class being transformed
    std::shared_ptr<types::DefinedType> currentClass =
        std::shared_ptr<types::DefinedType>(nullptr);

  public:
    // Module given to us so we can
    // identify where in the program we are.
    std::shared_ptr<ir::Module> module = nullptr;

  private:
    /// Utility function to get a primitive type
    /// @param name Type name to search for
    /// @return Primitive type shared pointer
    std::shared_ptr<types::Type> getPrimitiveType(const std::string name) {
        auto [ty, found] = getItem(name);

        assert(found);
        assert(ty->isType());

        return ty->getType();
    }

  public:
    // Create a new instance of a context
    TransformContext(std::shared_ptr<ir::Module> mod);

    /// @brief Get the bool primitive type
    std::shared_ptr<types::Type> getBoolType() {
        return getPrimitiveType(SN_BOOL_TYPE);
    }
    /// @brief Get the string primitive type
    std::shared_ptr<types::Type> getStringType() {
        return getPrimitiveType(SN_STR_TYPE);
    }
    /// @brief Get the char primitive type
    std::shared_ptr<types::Type> getCharType() {
        return getPrimitiveType(SN_CHR_TYPE);
    }
    /// @brief Get the equivalent of `void*` type in C
    std::shared_ptr<types::Type> getCObjectType() {
        return getPrimitiveType(SN_COB_TYPE);
    }
    /// @brief Get the float 64 primitive type
    std::shared_ptr<types::Type> getF64Type() {
        return getPrimitiveType(SN_F64_TYPE);
    }
    /// @brief Get the float 32 primitive type
    std::shared_ptr<types::Type> getF32Type() {
        return getPrimitiveType(SN_F32_TYPE);
    }

    /// @brief Get the int 64 primitive type
    std::shared_ptr<types::Type> getInt64Type() {
        return getPrimitiveType(SN_INT64_TYPE);
    }
    /// @brief Get the int 32 primitive type
    std::shared_ptr<types::Type> getInt32Type() {
        return getPrimitiveType(SN_INT32_TYPE);
    }
    /// @brief Get the int 16 primitive type
    std::shared_ptr<types::Type> getInt16Type() {
        return getPrimitiveType(SN_INT16_TYPE);
    }
    /// @brief Get the int 8 primitive type
    std::shared_ptr<types::Type> getInt8Type() {
        return getPrimitiveType(SN_INT8_TYPE);
    }

    /// @brief Get the void type representation
    std::shared_ptr<types::Type> getVoidType() {
        return getPrimitiveType(SN_VOID_TYPE);
    }

    /// @return The current function being generated
    auto getCurrentFunction() { return currentFunction; }
    /// @brief Set a new function that's being generated
    void setCurrentFunction(std::shared_ptr<ir::Func> f) {
        currentFunction = f;
    }
    /// @return Get the parent class being transformed
    auto getCurrentClass() { return currentClass; }
    /// @brief Defined the new type being generated
    void setCurrentClass(std::shared_ptr<types::DefinedType> c) {
        currentClass = c;
    }

    /**
     * @brief Add function to stack.
     * We do this in it's own special function because
     * we need to do some extra steps first.
     *   1. Check if function already exists in the stack
     *   2. (exists) Get that item and append a function to it
     *   3. (does not exist) Create a new item initialized
     *      with the function trying to be defined.
     */
    void defineFunction(std::shared_ptr<ir::Func> fn) {
        auto name = createIdentifierName(fn->getName());
        auto item = cache->getTransformedFunction(name);
        if (item) {
            assert((*item)->isFunc());
            (*item)->addFunction(fn);
            return;
        }

        auto i = std::make_shared<transform::Item>(fn);
        cache->setTransformedFunction(name, i);
    }

    /**
     * @brief Create an unique identifier name
     *
     * @param name Base name to "unique-ify"
     * @param includeBase Include things like: modules, classes, etc
     * @return std::string UUID for the name.
     */
    std::string createIdentifierName(const std::string name,
                                     bool includeBase = true);

    ~TransformContext() noexcept = default;

  public:
    // The cache. Look at `class Cache` to know more
    // about it and what it does.
    Cache* cache;
    // Controls, manages and caches modules used when
    // importying other files into the current program
    std::unique_ptr<services::ImportService> imports;

  public:
    /// @brief get a saved state of the context
    std::shared_ptr<transform::ContextState> saveState();
    /// @brief set a state to the current context
    void setState(std::shared_ptr<transform::ContextState> s);
    /// @brief Execute function with saved state
    void withState(std::shared_ptr<transform::ContextState> s,
                   std::function<void()> cb);
};

} // namespace Syntax
} // namespace snowball

#endif // __SNOWBALL_TRANSFORM_CONTEXT_H_
