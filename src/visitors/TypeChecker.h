
#include "../ValueVisitor/Visitor.h"
#include "../ir/values/Value.h"
#include "../sourceInfo/DBGSourceInfo.h"
#include "../errors.h"
#include "../ast/errors/error.h"

#include <assert.h>
#include <optional>
#include <string>
#include <vector>

#ifndef __SNOWBALL_TYPECHECKER_H_
#define __SNOWBALL_TYPECHECKER_H_

namespace snowball {
namespace codegen {

namespace typecheck {
/**
 * @brief Context class used for the type checker
 * to store information about the current state of the type checker.
 */
class Context {
  // Current function being typechecked
  ir::Func* currentFunction = nullptr;

public:
  /// @return The current function being type checked
  auto getCurrentFunction() { return currentFunction; }
  /// @brief Set a new function that's being type checked
  void setCurrentFunction(ir::Func* f) { currentFunction = f; }

  /// @brief If we are in an unsafe context
  bool unsafeContext = false;

  Context() = default;

  std::vector<errors::SNError*> errors;
};
}; // namespace typecheck

/**
 * @brief TypeChecker class
 *
 * The TypeChecker class is responsible for performing comprehensive type checking
 * on the codebase once the Abstract Syntax Tree (AST) has been transformed into a module.
 * Type checking involves a thorough analysis of various aspects of the code to ensure
 * type-related correctness and coherence.
 *
 * During this phase, the TypeChecker examines and enforces a range of type-related rules
 * and validations. This includes but is not limited to:
 * - Verifying that types are consistent and compatible across different parts of the code.
 * - Validating the correctness of function calls, ensuring that the provided arguments
 *   match the expected parameter types and that the return types align appropriately.
 * - Cross-referencing variable assignments and expressions to confirm type compatibility.
 * - Detecting and reporting type mismatches, undefined symbols, and other potential issues.
 *
 * By meticulously evaluating the type-related aspects of the code, the TypeChecker contributes
 * to the overall robustness and reliability of the software. It aids developers in catching
 * subtle errors that might lead to runtime crashes or unexpected behavior, fostering a more
 * stable and predictable software development process.
 */
class TypeChecker : public AcceptorExtend<TypeChecker, codegen::ValueVisitor> {
  // Program represented by a module.
  std::shared_ptr<ir::Module> module;
  // Context used to type check
  typecheck::Context* ctx = new typecheck::Context();
  /**
   * @brief Checks if a variable is mutable. If the IR value is not a
   * variable successor, it will return if the mutability specified inside the
   * value type.
   */
  bool isMutable(std::shared_ptr<ir::Value> value);
  /**
   * Utility function to avoid using 'void' types
   * as values.
   * @example
   *   let a = hello() <- error: hello returns void
   */
  void cantBeVoid(DBGObject* dbg, types::Type* ty, const std::string& message = "");
  /// @brief Check if the value is mutable or not
  void checkMutability(ir::Call* p_node, std::shared_ptr<ir::Func> fn, std::shared_ptr<ir::Value> value);
  /// @brief True if the value is accessing "self"
  bool accessingSelf(std::shared_ptr<ir::Value> value);
  /// @brief It performs checks on a function declaration
  void checkFunctionDeclaration(ir::Func* p_node);
  /// @brief It performs fixes to the generated types
  /// @example Fixing vtables with overriden members
  void fixTypes(std::shared_ptr<types::BaseType> ty);
  /// @brief Type check enum initializations
  void checkEnumInit(ir::Call* p_node);

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
  void visit(ir::Value* v) { v->visit(this); }

#define VISIT(n) void visit(ir::n*) override;
#include "../defs/visits.def"
#undef VISIT

  /// @brief Create and append a new error
  template <Error err, typename Obj>
  void E(Obj dbg, const std::string& message = "", ErrorInfo info = {}) {
    ctx->errors.push_back(Syntax::EI<err>(dbg, message, info));
  }
};

} // namespace codegen
} // namespace snowball

#undef VISIT
#endif // __SNOWBALL_TYPECHECKER_H_
