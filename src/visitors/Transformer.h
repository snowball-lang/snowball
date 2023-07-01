
#include "../ast/syntax/nodes.h"
#include "../ast/types/DefinedType.h"
#include "../ast/types/FunctionType.h"
#include "../ast/types/PointerType.h"
#include "../ast/visitor/Visitor.h"
#include "../ir/module/Module.h"
#include "../ir/values/Argument.h"
#include "../ir/values/Call.h"
#include "../ir/values/ReferenceTo.h"
#include "../ir/values/Constants.h"
#include "../ir/values/Func.h"
#include "../ir/values/Return.h"
#include "../ir/values/ValueExtract.h"
#include "../utils/utils.h"

#include <assert.h>
#include <deque>
#include <memory>
#include <string>
#include <vector>

#ifndef __SNOWBALL_TRANSFORM_H_
#define __SNOWBALL_TRANSFORM_H_

#include "TransformContext.h"

#define ACCEPT(Node)               virtual void visit(Node* p_node) override;
#define SN_TRANSFORMER_VISIT(Node) void Transformer::visit(Node* p_node)

namespace snowball {
namespace Syntax {

/**
 * @class Transformer
 * @brief AST visitor that transforms nodes into instructions.
 *
 * The Transformer class is an AST visitor that iterates through the AST
 * and translates (or transforms) all nodes into instructions. The
 * resulting instruction sequence can be used for various purposes, such
 * as code generation, program optimization, or program analysis.
 *
 * @note This class assumes that the input AST is valid and conforms to
 * the expected syntax and structure. Any errors or inconsistencies in
 * the AST may result in incorrect or incomplete transformation results.
 *
 * @note This class extends the AcceptorExtend class and implements the
 * Visitor interface.
 */
class Transformer : public AcceptorExtend<Transformer, Visitor> {
    /// @brief a list of generated modules through the whole project
    std::vector<std::shared_ptr<ir::Module>> modules;
    /**
     * @brief This is just an alias type
     *  for functions that need these 4 return types
     *  as a result.
     */
    using StoreType =
            std::tuple<std::optional<std::shared_ptr<ir::Value>>,
                       std::optional<std::shared_ptr<types::Type>>,
                       std::optional<std::deque<std::shared_ptr<ir::Func>>>,
                       std::optional<std::vector<cacheComponents::Functions::FunctionStore>>,
                       std::optional<std::shared_ptr<ir::Module>>>;
    // Context used to keep track of what's going on
    // and to manage a stack.
    TransformContext* ctx;
    // Transformed value from the last call
    std::shared_ptr<ir::Value> value;
    /**
     * Function fetch response.
     *
     * This enum is used to represent the response of a function fetch
     * operation, which can result in several different errors, such as
     * "no matches found" (0x01) and "ambiguous function types" (0x02).
     *
     * @note An Ok response (0x00) is not actually an error.
     */
    enum FunctionFetchResponse
    {
        Ok = 0x00,
        NoMatchesFound = 0x01,
        AmbiguityConflict = 0x02,
        _Unknown = -0x01
    };
    /**
     * Deduce a function from its template arguments and its call
     * arguments.
     *
     * @param s           A FunctionStore object representing the
     * function to deduce.
     * @param arguments   A vector of shared pointers to Type objects
     * representing the call arguments.
     * @param generics    A vector of shared pointers to Type objects
     * representing the template arguments (default: empty vector).
     *
     * @example
     * myFunction<T>(a: T);
     * --------------------------
     * myFunction<String>("hello") -> myFunction<String> (success)
     * myFunction("hello")         -> myFunction<String> (success)
     * myFunction<String>(6)       -> error: types don't match
     *
     * myOtherFunction<T = String>()
     * --------------------------
     * myOtherFunction<i32>()      -> myFunction<i32>    (success)
     * myOtherFunction()           -> myFunction<String> (success)
     *
     * @return A pair of the deduced argument types and a message
     * indicating any errors (empty string if there was success).
     */
    std::pair<std::vector<std::shared_ptr<types::Type>>, std::string>
    deduceFunction(cacheComponents::Functions::FunctionStore s,
                   const std::vector<std::shared_ptr<types::Type>>& arguments,
                   const std::vector<std::shared_ptr<types::Type>>& generics = {});
    /**
     * @brief Deduces a type for a generic function.
     *
     * It checks if the parameter has already been given and it
     * increments the generic argument index. If it's not included, it
     * will try to find it inside the provided function arguments based
     * on type names.
     *  @c deduceFunction
     */
    std::optional<std::shared_ptr<types::Type>>
    deduceFunctionType(snowball::Syntax::Expression::Param* generic,
                       const std::vector<Expression::Param*>& fnArgs,
                       const std::vector<std::shared_ptr<types::Type>>& arguments,
                       const std::vector<std::shared_ptr<types::Type>>& generics,
                       const std::vector<std::shared_ptr<types::Type>>& deducedTypes);
    /**
     * Generates a list of members that a `DefinedType` can have in C++.
     *
     * The list includes both the class's own fields and the fields
     * inherited from its parent (if any). If the child class has a
     * member with the same name as the parent class's member, the
     * parent member is kept but only if their types match. If the types
     * don't match, an error is thrown.
     *
     * @param type a pointer to the `DefinedType` to generate the list
     * for.
     * @return a vector containing all the class's fields, including the
     * inherited ones.
     */
    std::vector<types::DefinedType::ClassField*>
    getMemberList(std::vector<Syntax::Statement::VariableDecl*> fieldNodes,
                  std::vector<types::DefinedType::ClassField*>
                          fields,
                  std::shared_ptr<types::DefinedType>
                          parent);
    /**
     * Generate a function if it exists on the function cache,
     * if it was already generated, we can just return the already
     * generated function.
     *  @c deduceFunction
     */
    std::tuple<cacheComponents::Functions::FunctionStore,
               std::vector<std::shared_ptr<types::Type>>,
               FunctionFetchResponse>
    getBestFittingFunction(const std::vector<cacheComponents::Functions::FunctionStore>& overloads,
                           const std::vector<std::shared_ptr<types::Type>>& arguments,
                           const std::vector<Expression::TypeRef*>& generics = {},
                           bool isIdentifier = false);
    /**
     * @brief Compares if generics equal by checking both classes.
     * @note (1) This function will also generate the @param ty generics
     * if there are any present.
     * @note (2) The function shall only be called when checking a type
     * reference from the AST and an **already-generated** type fetched
     * from the cache.
     */
    bool typeGenericsMatch(Expression::TypeRef* ty, std::shared_ptr<types::Type> comp);
    /**
     * @brief It generates a type alias based on the `TypeRef` given to
     * us.
     * @note It also executes some checks such as generic checks and
     * more
     */
    std::shared_ptr<types::Type> transformTypeAlias(const std::string& uuid,
                                                    cacheComponents::Types::TypeStore& base,
                                                    Expression::TypeRef* typeRef);
    /**
     * @brief Fetch a function and get it's most fitting overload.
     *
     * The way we fetch a function is by firstly check on the cache
     * if the generated function has already been transformed. If not,
     * we will get the function overload and get the most fitting one.
     *
     *  @c deduceFunction @c getBestFittingFunction
     */
    std::shared_ptr<ir::Func>
    getFunction(DBGObject* dbgInfo,
                std::tuple<std::optional<std::shared_ptr<ir::Value>>,
                           std::optional<std::shared_ptr<types::Type>>,
                           std::optional<std::deque<std::shared_ptr<ir::Func>>>,
                           std::optional<std::vector<cacheComponents::Functions::FunctionStore>>,
                           std::optional<std::shared_ptr<ir::Module>>,
                           bool /* Accept private members */>
                        stores,
                const std::string& name,
                const std::vector<std::shared_ptr<types::Type>>& arguments,
                const std::vector<Expression::TypeRef*>& generics = {},
                bool isIdentifier = false);
    /**
     * @brief Transform a function that hasn't been generated yet.
     * @arg arguments - deduced arguments to unify
     */
    std::shared_ptr<ir::Func>
    transformFunction(cacheComponents::Functions::FunctionStore node,
                      const std::vector<std::shared_ptr<types::Type>>& deducedTypes,
                      bool isEntryPoint = false);
    /**
     * @brief Gets the `real` user defined list for the arguments.
     * This is because, when generating a function, we add the "self"
     * paramter if it's a non-static class method. We want to create
     * custom errors if a non-static method is called as if it was one
     * and there for we need to get this "real" list to avoid "no
     * matched functions" error.
     */
    std::vector<Expression::Param*>
    getActualFunctionArgs(cacheComponents::Functions::FunctionStore node);
    /**
     * @brief Checks if the current class in the context is in the same
     * context as @param ty.
     *
     * @example This can be used to check whether or not a private
     * member can be accessed from a certain context or scope.
     */
    bool isInClassContext(std::shared_ptr<types::Type> ty);
    /**
     * Retrieves the boolean value of the given shared pointer to an
     * ir::Value object.
     *
     * @param value A shared pointer to an ir::Value object to retrieve
     * the boolean value from.
     * @return A shared pointer to an ir::Value object representing the
     * boolean value of the given value object.
     */
    std::shared_ptr<ir::Value> getBooleanValue(std::shared_ptr<ir::Value> value);
    /**
     * @brief It imports and generates the core runtime classes and
     * functions for basic snowball functionality.
     */
    void initializeCoreRuntime();
    /**
     * Check if the current module has a valid (or private) context.
     *
     * @param mod               A shared pointer to an ir::Module object
     * representing the module to check.
     * @param isInClassContext  A boolean flag indicating whether the
     * check should consider the current context to be a class context.
     *
     * @return True if the module has a valid context, false otherwise.
     */
    bool isInModuleContext(std::shared_ptr<ir::Module> mod);
    /**
     * @brief It generates a a new types::Type instance from a
     * Statement::Base pointer.
     *
     * It only accepts `ClassDef` or `TypeAlias`. It's purpose it to
     * make sure the implementation of a new type is always up to date
     * in case the functionality us being updated.
     *
     * @note If the statement type is not supported, it will just panic!
     * @arg typeRef is only needed if base is `ClassDef`!
     */
    std::shared_ptr<types::Type> transformTypeFromBase(const std::string& uuid,
                                                       cacheComponents::Types::TypeStore& base,
                                                       Expression::TypeRef* typeRef);
    /**
     * Transforms a given special type reference into a shared pointer
     * to Type.
     *
     * @param ty A pointer to the Expression::TypeRef that represents
     * the special type.
     * @return A shared pointer to the Type that corresponds to the
     * special type.
     *
     * This function is used to transform a special type reference,
     * represented by a pointer to an Expression::TypeRef, into a shared
     * pointer to the corresponding Type. The Type returned by this
     * function will be used to represent the special type in the rest
     * of the program.
     *
     * @note It returns a null pointer of it didnt handle any special
     * type!
     */
    std::shared_ptr<types::Type> transformSpecialType(Expression::TypeRef* ty);
    /**
     * Returns a nicely formatted base name for the given set of
     * components.
     *
     * @param base A tuple containing the components to use when
     * constructing the base name.
     * @return A string containing the constructed base name.
     */
    std::string getNiceBaseName(
            std::tuple<std::optional<std::shared_ptr<ir::Value>>,
                       std::optional<std::shared_ptr<types::Type>>,
                       std::optional<std::deque<std::shared_ptr<ir::Func>>>,
                       std::optional<std::vector<cacheComponents::Functions::FunctionStore>>,
                       std::optional<std::shared_ptr<ir::Module>>,
                       bool /* (Ignore) Accept private members */>
                    base);
    /**
     * Check if the body of a function returns a value.
     *
     * This function takes a vector of Node pointers as input,
     * representing the statements in the body of a function. It then
     * checks whether the function returns a value by examining the AST
     * inside a body.
     *
     * @param exprs A vector of Node pointers representing the
     * statements in the body of a function.
     *
     * @return      A boolean indicating whether the function returns a
     * value.
     */
    bool bodyReturns(std::vector<Node*> exprs);
    /**
     * It executes a variaety of user-defined tests for a class/function/...
     * generics. If there are no tests, it does not do anything.
     *
     * @note If any test fail, an error would be reported meaning that if
     *  the program is still being executed all tests had passed.
     */
    void executeGenericTests(
            Syntax::Expression::WhereClause* clause, std::shared_ptr<types::Type> generic);
    /**
     * @brief Creates a type.
     *
     * It creates a new user defined type and adds it to the already
     * generated type cache. When generating a new class, each function
     * will be generated but not before.
     *
     * @note if the class contains generics, it will not be stored
     * inside the stack once it has been generated. Instead, it will be
     * stored in a special cache component for generic types. Keep in
     * mind that generated functions from classes with generics *will*
     * be stored in the stack but it will contain the class mangle in
     * the UUID.
     *
     * @example of function stored into the stack from a generic class.
     *    stack[class<T>.function(n)] :
     *      -> [module uuid].class:[# overload of class].function
     */
    std::shared_ptr<types::DefinedType>
    transformClass(const std::string& uuid,
                   cacheComponents::Types::TypeStore& classStore,
                   Expression::TypeRef* typeRef = nullptr);
    /**
     * @brief Get a value from an index node.
     * @return It may return a value, a type pointer or a vector
     * containing function overloads
     */
    std::pair<std::tuple<std::optional<std::shared_ptr<ir::Value>>,
                         std::optional<std::shared_ptr<types::Type>>,
                         std::optional<std::deque<std::shared_ptr<ir::Func>>>,
                         std::optional<std::vector<cacheComponents::Functions::FunctionStore>>,
                         std::optional<std::shared_ptr<ir::Module>>,
                         bool /* Accept private members */>,
              std::optional<std::shared_ptr<ir::Value>>>
    getFromIndex(DBGSourceInfo* dbgInfo, Expression::Index* index, bool isStatic);
    /**
     * @brief Get a value from an identifier.
     * @return It may return a value, a type pointer or a vector
     * containing function overloads
     */
    StoreType getFromIdentifier(DBGSourceInfo* dbgInfo,
                                const std::string identifier,
                                std::vector<Expression::TypeRef*> generics = {},
                                const std::string uuid = "");
    /**
     * @brief Utility method to transform identifier nodes into a valid
     * set of arguments for @fn getFromIdentifier
     */
    StoreType getFromIdentifier(Expression::Identifier* s);
    /// @brief Give an identifier it's base.
    /// @example Hello -> Module::Class::Hello
    std::string getNameWithBase(const std::string name);
    /// @brief Transform the program entry point.
    void transformMainFunction(Statement::FunctionDef* p_node);
    /// @brief append a new module to the global generated modules list
    void addModule(std::shared_ptr<ir::Module> m);
    /// @brief Transforms a special type. For example, the

  public:
    Transformer(std::shared_ptr<ir::Module> mod, SourceInfo* srci);

    using AcceptorExtend<Transformer, Visitor>::visit;

    /// @return The resultant module.
    auto getModule() const;
    /// @brief Transform all the nodes parsed
    virtual void visit(std::vector<Node*>) override;

    /// @brief Transform a "parsed type" into a "real type"
    std::shared_ptr<types::Type> transformType(Expression::TypeRef* ty);
    /// @return a list of generated modules through the whole project
    std::vector<std::shared_ptr<ir::Module>> getModules() const;

#include "../defs/accepts.def"

    // Default destructor
    ~Transformer() noexcept = default;
};

} // namespace Syntax
} // namespace snowball

#undef ACCEPT
#endif // __SNOWBALL_TRANSFORM_H_
