
#include "../../common.h"
#include "../../constants.h"
#include "../../ir/values/Func.h"
#include "../../utils/utils.h"
#include "Type.h"

#include <memory>
#include <string>
#include <vector>

#ifndef __SNOWBALL_AST_FUNCTION_TYPES_H_
#define __SNOWBALL_AST_FUNCTION_TYPES_H_

/**
 * Function types are really insane. When checking
 * a function type, we must take into consideration
 * all the factors that make 2 functions equal.
 * This can be checked by checking:
 *   - function types, base type, return type, ...
 *
 * hold on, give me some (mathematical) examples, pls:
 *   - lets imagine the following function declaration.
 *
 *       pub fn incrementN(n: i32) i32 { return n++; }
 *
 *     This function will be mathematicaly considered as
 *     `λn.n+1`. In this example, we can see that function's
 *     return and first argument has type `i32`. These are all
 *     factors that we will take into consideration for checking
 *     whether 2 functions match or not.
 *
 *     In simple type theory, two functions are considered equal
 *     if they have the same type and produce the same output for the
 *     same input. For example, if we have two functions f and g of
 *     type A -> B, where A and B are types, f and g are considered
 *     equal if for all values x of type A, f(x) = g(x). This notion
 *     of equality between functions is known as extensionality.
 *
 *     Of course, this checking theory just checks for parameter types,
 *     but in snowball, we also some take more things into consideration
 *     whether `f(x) = g(x)` or `f(x) != g(x)`.
 */
namespace snowball {
namespace types {

class FunctionType : public AcceptorExtend<FunctionType, Type> {
  // Function's argument type.
  std::vector<Type*> args;
  // Function's return type.
  Type* retTy;
  // Whether or not a function is declared
  // as variadic.
  bool variadic = false;

public:
  FunctionType(
          std::vector<Type*> args,
          Type* retTy,
          bool isVariadic = false,
          bool isMutable = true,
          const std::string& name = "<fn type>"
  )
      : AcceptorExtend(Kind::TYPE, name, isMutable), args(args), retTy(retTy), variadic(isVariadic) { }
  FunctionType(const FunctionType& other) = default;

  /**
   * @param other another (non-functional) type.
   *
   * This function will always return false if the type
   * is not a functional type since you can't compare
   * functional types with "normal" types. e.g.:
   *    function void (i32) == string
   *
   * This will just wont work. C++ will just look for the
   * actual function corresponding to a FunctionType and this
   * function will just have the purpose as a fallback.
   */
  virtual bool is(Type* other) const override {
    if (auto f = utils::cast<FunctionType>(other)) { return is(f); }

    return false;
  }

  /**
   * @brief Check whether one function type matches
   * another function type.
   *
   * @param other Function type to check
   * @return true/false depending on the equality
   */
  virtual bool is(FunctionType* other) const;

  /// @return function argument types
  std::vector<Type*> getArgs() const { return args; }
  /// @return function return types
  Type* getRetType() const { return retTy; }
  /// @return If the function is declared as variadic
  bool isVariadic() { return variadic; }

  // std::string getName() const override; // TODO:

  /**
   * @brief Get the function represented as a "human-readable"
   *  string
   */
  std::string getPrettyName() const override;
  std::string getMangledName() const override;

public:
  /**
   * Create a function type based on the given node.
   *
   * @param fn Function value to process
   * @return FunctionType* resultant type
   */
  static FunctionType* from(ir::Func* fn, Syntax::Statement::FunctionDef* node = nullptr);

  virtual std::int64_t sizeOf() const override { return 8; }
  virtual std::int64_t alignmentOf() const override { return 8; }

  SNOWBALL_TYPE_COPIABLE(FunctionType)
};

}; // namespace types
}; // namespace snowball

#endif // __SNOWBALL_AST_FUNCTION_TYPES_H_
