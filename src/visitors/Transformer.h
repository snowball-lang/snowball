
#include "../ast/syntax/nodes.h"
#include "../ast/types/DefinedType.h"
#include "../ast/types/FunctionType.h"
#include "../ast/types/Interface.h"
#include "../ast/types/PointerType.h"
#include "../ast/types/ReferenceType.h"
#include "../ast/types/TypeAlias.h"
#include "../ast/visitor/Visitor.h"
#include "../builder/llvm/LLVMIRChunk.h"
#include "../ir/builder/IRBuilder.h"
#include "../ir/module/Module.h"
#include "../ir/values/Argument.h"
#include "../ir/values/Call.h"
#include "../ir/values/Constants.h"
#include "../ir/values/Dereference.h"
#include "../ir/values/Func.h"
#include "../ir/values/ReferenceTo.h"
#include "../ir/values/Return.h"
#include "../ir/values/Throw.h"
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
#define SN_TRANSFORMER_CAN_GENERATE(node)                                                                              \
  if (utils::is<Statement::BodiedFunction>(node) || utils::is<Statement::ImportStmt>(node) ||                      \
      utils::is<Statement::LLVMFunction>(node) || utils::is<Statement::ExternFnDef>(node) ||                       \
      utils::is<Statement::ConstructorDef>(node) || utils::is<Statement::Namespace>(node) ||                       \
      utils::is<Statement::DefinedTypeDef>(node) || utils::is<Statement::TypeAlias>(node) ||                       \
      utils::is<Macro>(node))

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
  using StoreType = std::tuple<
          std::optional<std::shared_ptr<ir::Value>>,
          std::optional<types::Type*>,
          std::optional<std::deque<std::shared_ptr<ir::Func>>>,
          std::optional<std::deque<Cache::FunctionStore>>,
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
  std::tuple<std::vector<types::Type*>, std::string, int> deduceFunction(
          cacheComponents::Functions::FunctionStore s,
          const std::vector<types::Type*>& arguments,
          const std::vector<types::Type*>& generics = {}
  );
  /**
   * @brief Deduces a type for a generic function.
   *
   * It checks if the parameter has already been given and it
   * increments the generic argument index. If it's not included, it
   * will try to find it inside the provided function arguments based
   * on type names.
   *  @c deduceFunction
   */
  std::pair<std::optional<types::Type*>, int> deduceFunctionType(
          snowball::Syntax::Expression::Param* generic,
          const std::vector<Expression::Param*>& fnArgs,
          const std::vector<types::Type*>& arguments,
          const std::vector<types::Type*>& generics,
          const std::vector<types::Type*>& deducedTypes
  );
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
  std::vector<types::DefinedType::ClassField*> getMemberList(
          std::vector<Syntax::Statement::VariableDecl*> fieldNodes,
          std::vector<types::DefinedType::ClassField*> fields,
          types::DefinedType* parent
  );
  /**
   * Generate a function if it exists on the function cache,
   * if it was already generated, we can just return the already
   * generated function.
   *  @c deduceFunction
   */
  std::tuple<Cache::FunctionStore, std::vector<types::Type*>, FunctionFetchResponse> getBestFittingFunction(
          const std::deque<Cache::FunctionStore>& overloads,
          const std::vector<types::Type*>& arguments,
          const std::vector<Expression::TypeRef*>& generics = {},
          bool isIdentifier = false
  );
  /**
   * It tries to check if a type can be "casted" into another type.
   * @note It will return CastType::None if the types are not compatible.
   *  we don't return valid cast if they are the same type, because that
   *  is not a cast
   */
  enum class CastType
  {
    NoCast,
    Valid,
    AutoDeref,
    AutoRef,
    ToPointer
  };
  CastType canCast(types::Type* from, types::Type* to);
  /**
   * @brief Compares if generics equal by checking both classes.
   * @note (1) This function will also generate the @param ty generics
   * if there are any present.
   * @note (2) The function shall only be called when checking a type
   * reference from the AST and an **already-generated** type fetched
   * from the cache.
   */
  bool typeGenericsMatch(Expression::TypeRef* ty, types::Type* comp);
  /**
   * @brief It performs a type extension from the given AST node.
   * @note It will error if the type is not a class or if the class
   * does not exist.
   *
   * @param node The AST node to extend from.
   * @param uuid The UUID of the class to extend from.
   */
  void transformTypeExtension(Statement::DefinedTypeDef* node, std::string uuid);
  /**
   * @brief It generates super call and variale assignment for the
   *  class.
   * @return Both the super call and generated assigment values as if it was
   *  a block. (super call is the second pair argument)
   */
  std::pair<std::vector<std::shared_ptr<ir::Value>>, std::shared_ptr<ir::Call>>
  transformConstructor(Statement::ConstructorDef* p_node);
  /**
   * @brief It generates a type alias based on the `TypeRef` given to
   * us.
   * @note It also executes some checks such as generic checks and
   * more
   */
  types::Type*
  transformTypeAlias(const std::string& uuid, cacheComponents::Types::TypeStore& base, Expression::TypeRef* typeRef);
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
          DBGObject* dbgInfo,
          std::tuple<
                  std::optional<std::shared_ptr<ir::Value>>,
                  std::optional<types::Type*>,
                  std::optional<std::deque<std::shared_ptr<ir::Func>>>,
                  std::optional<std::deque<Cache::FunctionStore>>,
                  std::optional<std::shared_ptr<ir::Module>>,
                  bool /* Accept private members */> stores,
          const std::string& name,
          std::vector<types::Type*> arguments,
          const std::vector<Expression::TypeRef*>& generics = {},
          bool isIdentifier = false,
          bool hasSelf = false
  );
  /**
   * @brief It asserts that a type is `Sized`.
   * @note It will error if the type is not sized.
   * @param message The message to display if the type is not sized.
   * @param dbgInfo The debug information to use when reporting an error.
   * @note Message format will contain following string arguments:
   * - The first one is the type name.
   */
  void assertSizedType(types::Type* ty, const std::string message, DBGObject* dbgInfo);
  /**
   * It decides whether or not a generated function should be used or if
   *  and overloaded function should by checking the closest match.
   */
  std::shared_ptr<ir::Func>
  shouldReturnOverload(std::shared_ptr<ir::Func> fn, std::deque<std::shared_ptr<ir::Func>> overloads);
  /**
   * @brief Transform a function that hasn't been generated yet.
   * @arg arguments - deduced arguments to unify
   */
  std::shared_ptr<ir::Func> transformFunction(
          cacheComponents::Functions::FunctionStore node,
          const std::vector<types::Type*>& deducedTypes,
          bool isEntryPoint = false,
          std::deque<std::shared_ptr<ir::Func>> overloads = {}
  );
  /**
   * @brief Gets the `real` user defined list for the arguments.
   * This is because, when generating a function, we add the "self"
   * paramter if it's a non-static class method. We want to create
   * custom errors if a non-static method is called as if it was one
   * and there for we need to get this "real" list to avoid "no
   * matched functions" error.
   */
  std::vector<Expression::Param*> getActualFunctionArgs(cacheComponents::Functions::FunctionStore node);
  /**
   * @brief Checks if the current class in the context is in the same
   * context as @param ty.
   *
   * @example This can be used to check whether or not a private
   * member can be accessed from a certain context or scope.
   */
  bool isInClassContext(types::Type* ty);
  /**
   * @brief It generates macros. It will also generate the body of
   * the macro.
   */
  void transformMacro(Expression::PseudoVariable* p_node, transform::MacroInstance* macro);
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
   * @brief It generates all the macros for every module.
   */
  void initializePerModuleMacros();
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
   * @brief It get's the correct UUID for the given builtin type for a given type.
   * @param ty The type to get the builtin type from.
   * @note It will return a nullptr if the type is not a pointer.
   */
  std::string getBuiltinTypeUUID(types::Type* ty, const std::string& name, types::Type* original = nullptr);
  /**
   * @brief It generates a a new types::Type instance from a
   * Statement::Base pointer.
   *
   * It only accepts `DefinedTypeDef` or `TypeAlias`. It's purpose it to
   * make sure the implementation of a new type is always up to date
   * in case the functionality us being updated.
   *
   * @note If the statement type is not supported, it will just panic!
   * @arg typeRef is only needed if base is `DefinedTypeDef`!
   */
  types::Type*
  transformTypeFromBase(const std::string& uuid, cacheComponents::Types::TypeStore& base, Expression::TypeRef* typeRef);
  /**
   * @brief It tryes to cast a value to x type. If it fails, it will
   * return a nullptr.
   */
  std::shared_ptr<ir::Value> tryCast(std::shared_ptr<ir::Value> value, types::Type* type);
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
  types::Type* transformSpecialType(Expression::TypeRef* ty);
  /**
   * Returns a nicely formatted base name for the given set of
   * components.
   *
   * @param base A tuple containing the components to use when
   * constructing the base name.
   * @return A string containing the constructed base name.
   */
  std::string getNiceBaseName(std::tuple<
                              std::optional<std::shared_ptr<ir::Value>>,
                              std::optional<types::Type*>,
                              std::optional<std::deque<std::shared_ptr<ir::Func>>>,
                              std::optional<std::deque<Cache::FunctionStore>>,
                              std::optional<std::shared_ptr<ir::Module>>,
                              bool /* (Ignore) Accept private members */> base);
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
   * @return A boolean indicating whether the function returns a
   * value.
   */
  bool bodyReturns(std::vector<Node*> exprs);
  /**
   * It returns information about an expansion.
   * @note It will return a nullptr if the expansion is not valid.
   */
  const DBGObject*& getExpansionData();
  /**
   * It executes a variaety of user-defined tests for a class/function/...
   * generics. If there are no tests, it does not do anything.
   *
   * @note If any test fail, an error would be reported meaning that if
   *  the program is still being executed all tests had passed.
   */
  void executeGenericTests(Syntax::Expression::WhereClause* clause, types::Type* generic, const std::string& name);
  /**
   * @brief It "implements" the types into a class.
   */
  void implementTypes(
          types::DefinedType* ty,
          std::vector<Expression::TypeRef*> types,
          std::vector<Statement::FunctionDef*>& functions
  );
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
  types::BaseType* transformClass(
          const std::string& uuid, cacheComponents::Types::TypeStore& classStore, Expression::TypeRef* typeRef = nullptr
  );
  /**
   * Fetch the builder from the current context.
   */
  ir::IRBuilder& getBuilder();
  /**
   * @brief Get a value from an index node.
   * @return It may return a value, a type pointer or a vector
   * containing function overloads
   */
  std::pair<
          std::tuple<
                  std::optional<std::shared_ptr<ir::Value>>,
                  std::optional<types::Type*>,
                  std::optional<std::deque<std::shared_ptr<ir::Func>>>,
                  std::optional<std::deque<Cache::FunctionStore>>,
                  std::optional<std::shared_ptr<ir::Module>>,
                  bool /* Accept private members */>,
          std::optional<std::shared_ptr<ir::Value>>>
  getFromIndex(DBGSourceInfo* dbgInfo, Expression::Index* index, bool isStatic);
  /**
   * @brief Get a value from an identifier.
   * @return It may return a value, a type pointer or a vector
   * containing function overloads
   */
  StoreType getFromIdentifier(
          DBGSourceInfo* dbgInfo,
          const std::string identifier,
          std::vector<Expression::TypeRef*> generics = {},
          const std::string uuid = ""
  );
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
  /// @brief Transform a node into a value.
  std::shared_ptr<ir::Value> trans(Node* node);
  /// @brief Transform a node into a list of LLVM IR chunks.
  /// @example
  ///   %0 = alloca {=MyClassType}
  ///  This will return a list of chunks:
  ///   [0]: { type: LLCode, code: "%0 = alloca " }
  ///   [1]: { type: TypeAccess, ty: MyClassType }
  std::vector<LLVMIRChunk> getLLVMBody(std::string block, std::vector<Syntax::Expression::TypeRef*> getTypesUsed);

public:
  Transformer(
          std::shared_ptr<ir::Module> mod, const SourceInfo* srci, bool allowTests = false, bool allowBenchmark = false
  );

  using AcceptorExtend<Transformer, Visitor>::visit;
  using AcceptorExtend<Transformer, Visitor>::visitGlobal;

  /// @return The resultant module.
  auto getModule() const;
  /// @brief Transform all the nodes parsed
  virtual void visitGlobal(std::vector<Node*>) override;

  /// @brief Transform a "parsed type" into a "real type"
  types::Type* transformType(Expression::TypeRef* ty);
  /// @brief Transform a "parsed type" into a "real type" and it checks if
  ///        the type is sized.
  types::Type* transformSizedType(
          Expression::TypeRef* ty,
          bool ignoreVoid = false,
          const std::string message = "Expected type '%s' to be sized!"
  );
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
