
#include "../DBGSourceInfo.h"
#include "../ValueVisitor/Visitor.h"
#include "../ir/values/Value.h"

#include <assert.h>
#include <string>
#include <vector>

#ifndef __SNOWBALL_TYPECHECKER_H_
#define __SNOWBALL_TYPECHECKER_H_

/**
 * @brief Type checker class
 *
 * This class type checks everything after the
 * AST has been converted into a module.
 *
 * This type checks may be things like; Checking
 * if types equal, validating function calls, etc.
 */
namespace snowball {
namespace codegen {

namespace typecheck {
/**
 * @brief Context class used for the type checker
 */
class Context {
    // Current function being typechecked
    ptr<ir::Func> currentFunction = nullptr;

  public:
    /// @return The current function being type checked
    auto getCurrentFunction() { return currentFunction; }
    /// @brief Set a new function that's being type checked
    void setCurrentFunction(ptr<ir::Func> f) { currentFunction = f; }

    Context() = default;
};
}; // namespace typecheck

class TypeChecker : public AcceptorExtend<TypeChecker, codegen::ValueVisitor> {

    // Program represented by a module.
    std::shared_ptr<ir::Module> module;
    // Context used to type check
    ptr<typecheck::Context> ctx = new typecheck::Context();

    /**
     * Utility function to avoid using 'void' types
     * as values.
     * @example
     *   let a = hello() <- error: hello returns void
     */
    void cantBeVoid(ptr<DBGObject> dbg, std::shared_ptr<types::Type> ty,
                    const std::string& message = "");

  public:
    TypeChecker(std::shared_ptr<ir::Module> mod);
    ~TypeChecker() noexcept = default;

    /**
     * @brief Start type checking
     *
     * Here, we type check everything on the modules
     * after we generated the AST into a tree of values.
     */
    void codegen() override;

  private:
    /// @brief Typecheck the value given
    void visit(ptr<ir::Value> v) { v->visit(this); }

#define VISIT(n) void visit(ptr<ir::n>) override;
#include "../ValueVisitor/Visits.def"
#undef VISIT
};

} // namespace codegen
} // namespace snowball

#undef VISIT
#endif // __SNOWBALL_TYPECHECKER_H_