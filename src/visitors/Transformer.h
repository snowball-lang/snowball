
#include "../ast/syntax/nodes.h"
#include "../ast/types/DefinedType.h"
#include "../ast/types/FunctionType.h"
#include "../ast/visitor/Visitor.h"
#include "../ir/module/Module.h"
#include "../ir/values/Argument.h"
#include "../ir/values/Call.h"
#include "../ir/values/Constants.h"
#include "../ir/values/Func.h"
#include "../ir/values/Return.h"
#include "../ir/values/ValueExtract.h"
#include "../utils/utils.h"

#include <assert.h>
#include <memory>
#include <string>
#include <vector>

#ifndef __SNOWBALL_TRANSFORM_H_
#define __SNOWBALL_TRANSFORM_H_

#include "TransformContext.h"

#define ACCEPT(Node)               virtual void visit(ptr<Node> p_node) override;
#define SN_TRANSFORMER_VISIT(Node) void Transformer::visit(ptr<Node> p_node)

namespace snowball {
namespace Syntax {

/**
 * The transformer is an AST visitor that iterates
 * through the AST and translates (or transforms)
 * all nodes into instructions.
 *
 * This will be much more easyer to analize and
 * generate the program.
 */
class Transformer : public AcceptorExtend<Transformer, Visitor> {
    /// @brief a list of generated modules through the whole project
    std::vector<std::shared_ptr<ir::Module>> modules;
    /**
     * @brief This is just an alias type
     *  for functions that need these 4 return types
     *  as a result.
     */
    using StoreType = std::tuple<
        std::optional<std::shared_ptr<ir::Value>>,
        std::optional<std::shared_ptr<types::Type>>,
        std::optional<std::vector<std::shared_ptr<ir::Func>>>,
        std::optional<std::vector<cacheComponents::Functions::FunctionStore>>,
        std::optional<std::shared_ptr<ir::Module>>>;
    // Context used to keep track of what's going on
    // and to manage a stack.
    ptr<TransformContext> ctx;
    // Transformed value from the last call
    std::shared_ptr<ir::Value> value;
    /**
     * @brief Function fetch response .
     * This is used after we fetched a function from
     * our stack/cache.
     *
     * There can be several different
     * errors such as: no matches found (0x01) and
     * ambiguos function types (0x02).
     *
     * This is a better
     * way to get the error reason instead of just using
     * booleans.
     *
     * @note Ok (0x00) is not actually an error.
     */
    enum FunctionFetchResponse {
        Ok                = 0x00,
        NoMatchesFound    = 0x01,
        AmbiguityConflict = 0x02,
        _Unknown          = -0x01
    };
    /**
     * Deduce a function from it's template arguments and it's call arguments.
     * @example
     *   myFunction<T>(a: T);
     *   --------------------------
     *   myFunction<String>("hello") -> myFunction<String> | success
     *   myFunction("hello")         -> myFunction<String> | success
     *   myFunction<String>(6)       -> error: types dont match
     *   --------------------------
     *   myOtherFunction<T = String>()
     *   --------------------------
     *   myOtherFunction<i32>()      -> myFunction<i32>    | success
     *   myOtherFunction()           -> myFunction<String> | success
     *
     * @return pair: deduced argument types, message (empty string if there was
     * success)
     */
    std::pair<std::vector<std::shared_ptr<types::Type>>, std::string>
    deduceFunction(
        cacheComponents::Functions::FunctionStore s,
        const std::vector<std::shared_ptr<types::Type>>& arguments,
        const std::vector<std::shared_ptr<types::Type>>& generics = {});
    /**
     * @brief Deduces a type for a generic function.
     *
     * It checks if the parameter has already been given and it increments
     * the generic argument index. If it's not included, it will try to
     * find it inside the provided function arguments based on type names.
     *  @c deduceFunction
     */
    std::optional<std::shared_ptr<types::Type>> deduceFunctionType(
        ptr<snowball::Syntax::Expression::Param> generic,
        const std::vector<ptr<Expression::Param>>& fnArgs,
        const std::vector<std::shared_ptr<types::Type>>& arguments,
        const std::vector<std::shared_ptr<types::Type>>& generics,
        const std::vector<std::shared_ptr<types::Type>>& deducedTypes);
    /**
     * Generate a function if it exists on the function cache,
     * if it was already generated, we can just return the already
     * generated function.
     *  @c deduceFunction
     */
    std::tuple<cacheComponents::Functions::FunctionStore,
               std::vector<std::shared_ptr<types::Type>>, FunctionFetchResponse>
    getBestFittingFunction(
        const std::vector<cacheComponents::Functions::FunctionStore>& overloads,
        const std::vector<std::shared_ptr<types::Type>>& arguments,
        const std::vector<ptr<Expression::TypeRef>>& generics = {});
    /**
     * @brief Compares if generics equal by checking both classes.
     * @note (1) This function will also generate the @param ty generics if
     *  there are any present.
     * @note (2) The function shall only be called when checking a type
     * reference from the AST and an **already-generated** type fetched from the
     * cache.
     */
    bool typeGenericsMatch(ptr<Expression::TypeRef> ty,
                           std::shared_ptr<types::DefinedType> comp);
    /**
     * @brief Fetch a function and get it's most fitting overload.
     *
     * The way we fetch a function is by firstly check on the cache
     * if the generated function has already been transformed. If not,
     * we will get the function overload and get the most fitting one.
     *
     *  @c deduceFunction @c getBestFittingFunction
     */
    std::shared_ptr<ir::Func> getFunction(
        ptr<DBGObject> dbgInfo,
        std::tuple<std::optional<std::shared_ptr<ir::Value>>,
                   std::optional<std::shared_ptr<types::Type>>,
                   std::optional<std::vector<std::shared_ptr<ir::Func>>>,
                   std::optional<
                       std::vector<cacheComponents::Functions::FunctionStore>>,
                   std::optional<std::shared_ptr<ir::Module>>,
                   bool /* Accept private members */>
            stores,
        const std::string& name,
        const std::vector<std::shared_ptr<types::Type>>& arguments,
        const std::vector<ptr<Expression::TypeRef>>& generics = {});
    /**
     * @brief Transform a function that hasn't been generated yet.
     * @arg arguments - deduced arguments to unify
     */
    std::shared_ptr<ir::Func> transformFunction(
        cacheComponents::Functions::FunctionStore node,
        const std::vector<std::shared_ptr<types::Type>>& deducedTypes);
    /**
     * @brief Gets the `real` user defined list for the arguments.
     * This is because, when generating a function, we add the "self" paramter
     * if it's a non-static class method. We want to create custom errors if a
     * non-static method is called as if it was one and there for we need to get
     * this "real" list to avoid "no matched functions" error.
     */
    std::vector<ptr<Expression::Param>>
    getActualFunctionArgs(cacheComponents::Functions::FunctionStore node);
    /**
     * @brief Checks if the current class in the context is in the same context
     *  as @param ty.
     *
     * @example This can be used to check whether or not a private member can be
     *  accessed from a certain context or scope.
     */
    bool isInClassContext(std::shared_ptr<types::Type> ty);
    /**
     * @brief It checks if the current module has a valid (or private) context
     * to
     *  @param mod
     *
     * @c isInClassContext
     */
    bool isInModuleContext(std::shared_ptr<ir::Module> mod);
    /**
     * @brief Creates a type.
     *
     * It creates a new user defined type and adds it to the already
     * generated type cache. When generating a new class, each function
     * will be generated but not before.
     *
     * @note if the class contains generics, it will not be stored inside the
     *  stack once it has been generated. Instead, it will be stored in a
     * special cache component for generic types. Keep in mind that generated
     * functions from classes with generics *will* be stored in the stack but it
     * will contain the class mangle in the UUID.
     *
     * @example of function stored into the stack from a generic class.
     *    stack[class<T>.function(n)] :
     *      -> [module uuid].class:[# overload of class].function
     */
    std::shared_ptr<types::DefinedType>
    transformClass(const std::string& uuid,
                   cacheComponents::Types::TypeStore& classStore,
                   ptr<Expression::TypeRef> typeRef);
    /**
     * @brief Get a value from an index node.
     * @return It may return a value, a type pointer or a vector containing
     * function overloads
     */
    std::tuple<
        std::optional<std::shared_ptr<ir::Value>>,
        std::optional<std::shared_ptr<types::Type>>,
        std::optional<std::vector<std::shared_ptr<ir::Func>>>,
        std::optional<std::vector<cacheComponents::Functions::FunctionStore>>,
        std::optional<std::shared_ptr<ir::Module>>,
        bool /* Accept private members */>
    getFromIndex(ptr<DBGSourceInfo> dbgInfo, ptr<Expression::Index> index,
                 bool isStatic);
    /**
     * @brief Get a value from an identifier.
     * @return It may return a value, a type pointer or a vector containing
     * function overloads
     */
    StoreType
    getFromIdentifier(ptr<DBGSourceInfo> dbgInfo, const std::string identifier,
                      std::vector<ptr<Expression::TypeRef>> generics = {},
                      const std::string uuid                         = "");
    /// @brief Give an identifier it's base.
    /// @example Hello -> Module::Class::Hello
    std::string getNameWithBase(const std::string name);
    /// @brief Transform the program entry point.
    void transformMainFunction(ptr<Statement::FunctionDef> p_node);
    /// @brief append a new module to the global generated modules list
    void addModule(std::shared_ptr<ir::Module> m);
  public:
    Transformer(std::shared_ptr<ir::Module> mod, ptr<SourceInfo> srci);

    using AcceptorExtend<Transformer, Visitor>::visit;

    /// @return The resultant module.
    auto getModule() const;

    /// @brief Transform a "parsed type" into a "real type"
    std::shared_ptr<types::Type> transformType(ptr<Expression::TypeRef> ty);
    /// @return a list of generated modules through the whole project
    std::vector<std::shared_ptr<ir::Module>> getModules() const;
    
#include "../ast/syntax/accepts.def"

    // Default destructor
    ~Transformer() noexcept = default;
};

} // namespace Syntax
} // namespace snowball

#undef VISIT
#endif // __SNOWBALL_TRANSFORM_H_
