
#include "../ast/syntax/nodes.h"
#include "../ast/visitor/ASTContext.h"
#include "../ast/visitor/Visitor.h"
#include "../ir/builder/IRBuilder.h"
#include "../ir/values/Value.h"
#include "../services/ImportService.h"
#include "../sourceInfo/DBGSourceInfo.h"
#include "MacroInstance.h"
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
class TransformContext : public AcceptorExtend<TransformContext, ASTContext<transform::Item>> {
  // Current function being generated
  std::shared_ptr<ir::Func> currentFunction = std::shared_ptr<ir::Func>(nullptr);
  // Current class being transformed
  types::Type* currentClass = nullptr;
  // The IRBuilder instance that's being used to generate the IR
  ir::IRBuilder& builder;

 public:
  // Module given to us so we can
  // identify where in the program we are.
  std::shared_ptr<ir::Module> module = nullptr;
  // If test mode is enabled
  bool testMode = false;
  // If benchmark mode is enabled
  bool benchMode = false;
  // We are compiling the main module
  bool isMainModule = false;
  // A list of exported functions and variables without mangle
  std::vector<std::string> exported;
  /// @brief A stack of UUIDs that are used to generate
  ///  unique identifiers for things like functions, variables, etc.
  /// @note Only used for namespaces.
  /// @note The closest stack item will not be added to the UUID stack.
  std::vector<std::string> uuidStack = {};
  /// @brief The real class that the context is under. This
  ///  is useful (for example) when you want to generate functions
  ///  that got inherited but still want it to "be part of" the parent
  ///  type.
  types::Type* actuallCurrentClass = nullptr;
  /// @brief A node representing the last call being transformed sort of
  ///  like the first call in a backtrace list
  /// @todo maybe make it a list and display all of the calls if a flag like
  ///  "--show-full-backtrace" is set.
  Expression::FunctionCall* latestCall = nullptr;
  /// @brief The current macro instance being transformed
  std::vector<std::pair<DBGSourceInfo*, transform::MacroInstance*>> macroBacktrace = {};

 private:
  /// Utility function to get a primitive type
  /// @param name Type name to search for
  /// @return Primitive type shared pointer
  types::Type* getPrimitiveType(const std::string name) {
    auto [ty, found] = getItem(name);
    assert(found);
    assert(ty->isType());
    return ty->getType();
  }

 public:
  // Create a new instance of a context
  TransformContext(
          std::shared_ptr<ir::Module> mod, ir::IRBuilder& builder, bool testMode = false, bool benchMode = false);

  // clang-format off

    /// @brief Get the bool primitive type
    types::Type* getBoolType() { return new types::IntType(1); }
    /// @brief Get the char primitive type
    types::Type* getCharType() { return getPrimitiveType(SN_CHR_TYPE); }
    /// @brief Get the float 64 primitive type
    types::Type* getF64Type() { return new types::FloatType(64); }
    /// @brief Get the float 32 primitive type
    types::Type* getF32Type() { return new types::FloatType(32); }
    /// @brief Get the int 64 primitive type
    types::Type* getInt64Type() { return new types::IntType(64); }
    /// @brief Get the int 32 primitive type
    types::Type* getInt32Type() { return new types::IntType(32); }
    /// @brief Get the int 16 primitive type
    types::Type* getInt16Type() { return new types::IntType(16); }
    /// @brief Get the int 8 primitive type
    types::Type* getInt8Type() { return new types::IntType(8); }
    /// @brief Get the void type representation
    types::Type* getVoidType() { return getPrimitiveType(SN_VOID_TYPE); }
  // clang-format on

  /// @return The current function being generated
  auto getCurrentFunction() { return currentFunction; }
  /// @brief Set a new function that's being generated
  void setCurrentFunction(std::shared_ptr<ir::Func> f) { currentFunction = f; }
  /// @return Get the parent class being transformed
  auto getCurrentClass(bool actual = false) {
    return actual ? actuallCurrentClass == nullptr ? currentClass : actuallCurrentClass : currentClass;
  }
  /// @brief Defined the new type being generated
  void setCurrentClass(types::Type* c) { currentClass = c; }

  transform::MacroInstance* getCurrentMacro() {
    if (macroBacktrace.empty()) return nullptr;
    return macroBacktrace.back().second;
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
  void defineFunction(std::shared_ptr<ir::Func> fn, const std::string namePrefix = "") {
    auto fnName = fn->getName(true);
    auto name = namePrefix.empty() ? createIdentifierName(fnName) : namePrefix + "." + fnName;
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
  std::string createIdentifierName(const std::string name, bool includeBase = true);
  /**
   * @brief It creates an error tail from a certain dbg node
   */
  template <typename T>
  auto createErrorTail(T x, ErrorInfo info = {}) {
    return Syntax::EI<Error::BUG>(x, "", info);
  }

  ~TransformContext() noexcept = default;

 public:
  // The cache. Look at `class Cache` to know more
  // about it and what it does.
  Cache* cache;
  // Controls, manages and caches modules used when
  // importying other files into the current program
  std::unique_ptr<services::ImportService> imports;
  // A flag that shows if a function should be generated
  bool generateFunction = false;

 public:
  /// @brief get a saved state of the context
  std::shared_ptr<transform::ContextState> saveState();
  /// @brief set a state to the current context
  void setState(std::shared_ptr<transform::ContextState> s);
  /// @brief Execute function with saved state
  void withState(std::shared_ptr<transform::ContextState> s, std::function<void()> cb);
};

} // namespace Syntax
} // namespace snowball

#endif // __SNOWBALL_TRANSFORM_CONTEXT_H_
