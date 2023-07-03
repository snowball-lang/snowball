
#include "../../ValueVisitor/Visitor.h"
#include "../../ast/syntax/nodes.h"
#include "../../ast/types/DefinedType.h"
#include "../../ast/types/Type.h"
#include "../../common.h"
#include "Body.h"
#include "Value.h"
#include "Variable.h"
#include "VariableDeclaration.h"

#include <cassert>
#include <map>
#include <vector>

#ifndef __SNOWBALL_FUNC_VAL_H_
#define __SNOWBALL_FUNC_VAL_H_
namespace snowball {
namespace ir {

/// @brief Representation of a function in the IR
class Func : public AcceptorExtend<Func, Value>,
             public IdMixin,
             public AcceptorExtend<Func, Syntax::Statement::Privacy>,
             public AcceptorExtend<Func,
                                   Syntax::Statement::GenericContainer<
                                           std::pair<std::string, std::shared_ptr<types::Type>>>>,
             public AcceptorExtend<Func, Syntax::Statement::AttributeHolder<Attributes::Fn>> {
  public:
    // Utility types
    using FunctionArgs = std::list<std::pair<std::string, std::shared_ptr<Argument>>>;

  private:
    /// When a function is variadic, it means that
    /// it can take a variable number of arguments.
    bool variadic = false;
    /// A virtual function is a member function of a
    /// class that can be overridden in a derived class.
    /// When a virtual function is called through a pointer
    /// or reference to the base class, the implementation
    /// of the derived class is invoked instead of the
    /// implementation of the base class.
    /// @note If it's equal to "-1" that means that it does
    ///  not form part of a virtual table.
    int virtualIndex = -1;

    /// These are used to use the function without
    /// actually setting the body inside it, it's
    /// just a forward declaration.
    bool declaration = false;
    /// Function's identifier
    std::string identifier;
    /// Function's return type
    std::shared_ptr<types::Type> retTy;
    /// @brief Parent class that this function is defined
    ///  in.
    std::shared_ptr<types::DefinedType> parent = nullptr;

    /// Function parameters are the names listed in
    /// the function definition. Function arguments
    /// are the real values passed to (and received by)
    /// the function.
    FunctionArgs arguments;

    /// There are the instructions executed inside
    /// the function. note: if there is non, this means
    /// that the function could be potentially a declaration
    std::shared_ptr<Block> body;

    /// There are the LLVM Ir instructions executed inside
    /// the function
    std::string llvmBody;

    /// A list of variables used *anywhere* around the function.
    /// This is so that we allocate a new variable at the start
    /// of the function. We do this to avoid any kind of errors
    /// such as; allocating new memory each time we iterate in a loop.
    std::vector<std::shared_ptr<VariableDeclaration>> symbols;

    /// This is how the function will be exported. If the name is empty,
    /// snowball will mangle the name accordingly but if it's not, this
    /// string will be used as an external identifier. This is used for
    /// things such as; declaring the function entry point and declaring
    /// external functions
    std::string externalName;

    /// Functions can be declared static too! We have this utility
    /// variable to determine if the function is declared as one. Being
    /// declared as static may bring different meanings.
    /// @example Static function for a class
    bool _static = false;

    /// @brief A boolean attribute that indicates whether the function
    /// is used. This attribute is used inside "ir::Func" class to keep
    /// track of whether the function is used or not.
    /// @note The initial value of this attribute is false.
    bool used = false;

  public:
#define DEFAULT                                                                                    \
    bool declaration = false, bool variadic = false,                                               \
         std::shared_ptr<types::DefinedType> ty = nullptr

    explicit Func(std::string identifier, DEFAULT);
    explicit Func(std::string identifier, FunctionArgs arguments, DEFAULT);
    explicit Func(std::string identifier, std::shared_ptr<Block> body, DEFAULT);
    explicit Func(
            std::string identifier, std::shared_ptr<Block> body, FunctionArgs arguments, DEFAULT);

#undef DEFAULT

    /// @return Whether the function is variadic
    bool isVariadic() const { return variadic; }
    /// @return Whether the function is variadic
    bool isDeclaration() const { return declaration; }

    /// @return function's raw identifier
    virtual std::string getIdentifier();
    /// @return The same as @fn getIdentifier but it also handles
    ///  operator names.
    virtual std::string getName(bool ignoreOperators = false);
    /// @return mangled name for the function.
    virtual std::string getMangle();
    /// @return Function's pretty name for debbuging
    virtual std::string getNiceName();

    /// @brief Set a body to a function
    void setBody(std::shared_ptr<Block> p_body) { body = p_body; }
    /// @return Get body from function
    auto getBody() const { return body; }

    /// @brief Declare a new LLVM IR body
    /// @param llvmBody the LLVM IR instructions
    void setLLVMBody(std::string llvmBody) { this->llvmBody = llvmBody; }
    /// @return the LLVM ir body for this function
    auto getLLVMBody() {
        assert(!isDeclaration() && hasAttribute(Attributes::LLVM_FUNC));
        return llvmBody;
    }
    /// @brief Set arguments to a function
    void setArgs(FunctionArgs p_args) { arguments = p_args; }
    /// @return Get arguments from function
    /// @param ignoreSelf removes the `self` paramter (aka. the first /
    /// class parameter)
    ///  if it's set to `true`.
    FunctionArgs getArgs(bool ignoreSelf = false) const;

    /// @brief Set a return type to a function
    void setRetTy(std::shared_ptr<types::Type> p_ret) { retTy = p_ret; }
    /// @return Get function's return type.
    auto& getRetTy() const { return retTy; }

    /// @brief Set a return type to a function
    void addSymbol(std::shared_ptr<VariableDeclaration> v) { symbols.emplace_back(v); }
    /// @return Get function's return type.
    std::vector<std::shared_ptr<VariableDeclaration>>& getSymbols() {
        assert(!isDeclaration());
        return symbols;
    }
    /// @brief get from what parent this function is declared inside
    auto getParent() const { return parent; }
    /// @return whether or not the function is defiend within a
    ///  parent scope.
    bool hasParent() const { return getParent() != nullptr; }

    /// @brief Get the index were the function is located at inside the
    ///  virtual table.
    auto getVirtualIndex() const {
        assert(inVirtualTable());
        return virtualIndex;
    }
    /// @return Check if the function is part of a virtual table.
    bool inVirtualTable() const { return virtualIndex != -1; }
    /// @brief Set a new virtual table index.
    void setVirtualIndex(int x = -1) { virtualIndex = x; }

    /// @brief Set an external name to the function
    /// @c externalName
    void setExternalName(std::string n) { externalName = n; }
    /// @brief Declare the function as static or not
    void setStatic(bool s = false) { _static = s; }
    /// @return whether or not the function is static
    auto isStatic() { return _static; }
    /// @return true if the function is a class contructor
    bool isConstructor() const;

    // Set a visit handler for the generators
    SN_GENERATOR_VISITS
  public:
    /**
     * @brief Static function to detect if it's external or not
     * @c setExternalName @c externalName
     */
    static bool isExternal(std::string name);
    /**
     * @brief Static helper to check if argument size are valid.
     * @note this is used for checking between 2 arguments.
     *
     * @param isVariadic if the function is variadic, first list of
     *  arguments can be greater that the function arguments.
     */
    template <typename T>
    static bool argumentSizesEqual(std::vector<T> functionArgs,
                                   const std::vector<std::shared_ptr<types::Type>>
                                           arguments,
                                   bool isVariadic = false) {
        int numFunctionArgs = functionArgs.size();
        int numProvidedArgs = arguments.size();
        int numDefaultArgs = 0;
        // DUMP(std::is_same_v<T, Argument>::value)
        //  Calculate the number of default arguments
        if (numFunctionArgs > numProvidedArgs) {
            if constexpr (std::is_same_v<T, std::shared_ptr<Argument>>) {
                for (int i = numProvidedArgs; i < numFunctionArgs; i++) {
                    if (functionArgs.at(i)->hasDefaultValue()) {
                        numDefaultArgs++;
                    } else {
                        // If we encounter a non-default argument, stop
                        // counting
                        break;
                    }
                }
            }
        }

        return (numFunctionArgs - numDefaultArgs == numProvidedArgs) ||
                (numFunctionArgs <= arguments.size() && isVariadic);
    }
};

} // namespace ir
} // namespace snowball

#endif // __SNOWBALL_FUNC_VAL_H_
