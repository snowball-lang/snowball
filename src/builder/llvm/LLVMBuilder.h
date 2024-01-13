
#include "../../../app/cli.h"
#include "../../ValueVisitor/Visitor.h"
#include "../../ast/types/DefinedType.h"
#include "../../ast/types/FunctionType.h"
#include "../../ast/types/Interface.h"
#include "../../ast/types/EnumType.h"
#include "../../ast/types/PointerType.h"
#include "../../ast/types/ReferenceType.h"
#include "../../ast/types/TypeAlias.h"
#include "../../ast/errors/error.h"
#include "../../ir/id.h"
#include "../../ir/module/MainModule.h"
#include "../../ir/values/Func.h"
#include "../../ir/values/ReferenceTo.h"
#include "../../ir/values/Value.h"

#include <llvm/IR/Constants.h>
#include <llvm/IR/DIBuilder.h>
#include <llvm/IR/DebugInfoMetadata.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/Target/TargetMachine.h>

#include <cstdint>
#include <map>
#include <memory>

#ifndef __SNOWBALL_LLVM_BUILDER_H_
#define __SNOWBALL_LLVM_BUILDER_H_

namespace snowball {
namespace codegen {

namespace llvm_utils {
int typeIdxLookup(const std::string& name);
} // namespace llvm_utils

using namespace llvm_utils;

/**
 * @brief Some context so that we can know
 * where in the program we are located.
 */
class LLVMBuilderContext {
  // Current function being generated
  llvm::Function* currentFunction = nullptr;
  // Current IR function being generated
  ir::Func* currentIRFunction = nullptr;

  // All variables used around the program.
  // note: all of the llvm values are actually
  // "alloca" instructions.
  std::map<ir::id_t, llvm::Value*> symbols;
  // A map containing all the vtables for every single
  // type.
  std::map<ir::id_t, llvm::GlobalVariable*> vtables;
  // A container for all the vtable struct types.
  std::map<ir::id_t, llvm::StructType*> vtableType;

public:
  // A value used to return a struct from a function
  bool retValueUsedFromArg = false;
  // A value used to store a value into a variable
  llvm::Value* callStoreValue = nullptr;
  // A map of test functions containing their names
  std::vector<std::pair<ir::Func*, llvm::Function*>> tests;
  // A map of benchmark functions containing their names
  std::vector<std::pair<ir::Func*, llvm::Function*>> benchmarks;
  // If the module is compiled in test mode
  bool testMode = false;
  // If the module is compiled in benchmark mode
  bool benchmarkMode = false;
  /// @return Current function being generated
  auto getCurrentFunction() { return currentFunction; }
  /// @return Change the current function to a new one
  void setCurrentFunction(llvm::Function* fn) { currentFunction = fn; }
  /// @brief Reset the current function to a null pointer
  void clearCurrentFunction() { currentFunction = nullptr; }
  /// @return Current IR function being generated
  auto getCurrentIRFunction() { return currentIRFunction; }
  /// @return Change the current IR function to a new one
  void setCurrentIRFunction(ir::Func* fn) { currentIRFunction = fn; }
  /// @brief Reset the current IR function to a null pointer
  void clearCurrentIRFunction() { currentIRFunction = nullptr; }

  /// @return A full list of symbols used around the program
  auto& getAllSymbols() { return symbols; }
  /// @return Add a new symbol to the symbol map
  void addSymbol(ir::id_t i, llvm::Value* s) { symbols.emplace(i, s); }
  /// @brief Get the corresponding symbol to an id
  auto getSymbol(ir::id_t i) -> llvm::Value* { return symbols.at(i); }
  /// @brief Clear the symbol table
  void clearSymbols() { return symbols.clear(); }
  /// @return Add a new vtable to the vtable map
  void addVtable(ir::id_t i, llvm::GlobalVariable* s) { vtables.emplace(i, s); }
  /// @brief Get the corresponding vtable to an id
  auto getVtable(ir::id_t i) -> llvm::GlobalVariable* {
    auto item = vtables.find(i);
    return item == vtables.end() ? nullptr : item->second;
  }
  /// @return Add a new vtable to the vtable map
  void addVtableTy(ir::id_t i, llvm::StructType* s) { vtableType.emplace(i, s); }
  /// @brief Get the corresponding vtable to an id
  auto getVtableTy(ir::id_t i) -> llvm::StructType* {
    auto item = vtableType.find(i);
    return item == vtableType.end() ? nullptr : item->second;
  }
  // TODO: add a function to clear functions, symbols, etc as cleanup
  /// @brief A flag to avoid loading a value in memory
  bool doNotLoadInMemory = false;
  /// @brief Optimization level
  app::Options::Optimization optimizationLevel = app::Options::Optimization::OPTIMIZE_O0;
  // Type information about ALLLL the types being used
  std::map<ir::id_t, std::shared_ptr<types::BaseType>> typeInfo;
  /// @brief Type info for closures
  struct ClosureContext {
    std::vector<ir::id_t> variables;
    llvm::Value* closure = nullptr; // Closure allocation
    llvm::StructType* closureType = nullptr;
  };
  /// @brief Closure map for all the closures
  std::map<ir::id_t, ClosureContext> closures;
  /// @brief Loop information
  struct {
    // The continue block for the current loop
    llvm::BasicBlock* continueBlock = nullptr;
    // The break block for the current loop
    llvm::BasicBlock* breakBlock = nullptr;
  } loop;
};

/**
 * An LLVM builder that will transform the internal
 * representation of the program into a LLVM module.
 * This module can then be compiled into many different
 * things.
 * @see https://llvm.org/docs/LangRef.html
 */
class LLVMBuilder : AcceptorExtend<LLVMBuilder, ValueVisitor> {
  // A global map to keep track of all processed
  // functions.
  std::map<ir::id_t, llvm::Function*> funcs;
  // Some sort of cache to prevent struct-like types
  // from being generated over and over again.
  std::map<ir::id_t, llvm::Type*> types;
  // Internal module given by the internal representation
  // of the program.
  std::shared_ptr<ir::Module> iModule;
  // Context used all around the codegen process
  std::unique_ptr<LLVMBuilderContext> ctx = std::make_unique<LLVMBuilderContext>();
  /**
   * Struct containing all debug information
   * tools needed.
   */
  struct DebugInfo {
    /// Current compilation unit
    llvm::DICompileUnit* unit = nullptr;
    /// Debug info builder
    std::unique_ptr<llvm::DIBuilder> builder = nullptr;
    // Debug flag
    bool debug = false;

    // Create a new DIFile for llvm
    llvm::DIFile* getFile(const std::string& path);
  } dbg;
  /**
   * Helper struct containing all the llvm helper functions
   * needed. This is used to avoid having to write a lot of
   * boilerplate code.
   * @see https://llvm.org/doxygen/classllvm_1_1IRBuilder.html
   */
  struct {
    /**
     * Create a new llvm value.
     * @return Created llvm value.
     */
    template <typename Inst, class... Args>
    static Inst* create(Args&&... args) {
      return Inst::Create(std::forward<Args>(args)...);
    }
    /**
     * Create a new llvm instruction.
     * @return Created llvm struction.
     */
    template <typename Inst, class... Args>
    static Inst* insert(Args&&... args) {
      return new Inst(std::forward<Args>(args)...);
    }
  } h;
  /// Create a new alloca instruction
  llvm::AllocaInst* createAlloca(llvm::Type* ty, std::string name = "") {
    auto backupBlock = builder->GetInsertBlock();
    auto entryBlock = ctx->getCurrentFunction()->getEntryBlock().getTerminator();
    if (entryBlock) {
      builder->SetInsertPoint(entryBlock);
    }
    auto alloca = builder->CreateAlloca(ty, nullptr, name);
    builder->SetInsertPoint(backupBlock);
    return alloca;
  }
  /// Information for each try-catch block.
  struct TryCatchInfo {
    /// The catch block
    llvm::BasicBlock* catchBlock;
    /// Catch route block
    llvm::BasicBlock* catchRouteBlock;
    /// All handlers for this try-catch block
    std::vector<llvm::BasicBlock*> handlers;
    /// All catch variables for this try-catch block
    std::vector<std::shared_ptr<ir::VariableDeclaration>> catchVars;
    /// Stores the exception pad
    llvm::Value* exceptionPad = nullptr;
  };
  /// A stack containing all the try-catch blocks
  std::vector<TryCatchInfo> tryCatchStack;
  // LLVM IR module that acts as a top level container of
  // all other LLVM Intermediate Representation (IR) objects
  std::unique_ptr<llvm::Module> module;
  // An unique pointer for an instruction builder.
  std::unique_ptr<llvm::IRBuilder<>> builder;
  // LLVM context for the module
  std::unique_ptr<llvm::LLVMContext> context;
  // Last compiled (generated) value
  llvm::Value* value;
  // Target machine that the module will be compiled into
  llvm::TargetMachine* target;

public:
  // Create a new instance of a llvm builder
  LLVMBuilder(
          std::shared_ptr<ir::MainModule> mod,
          app::Options::Optimization optimizationLevel = app::Options::Optimization::OPTIMIZE_O0,
          bool testMode = false,
          bool benchmarkMode = false
  );
  /**
   * @brief Dump the LLVM IR code to stdout.
   *
   * note: this must only be used for debug
   * purposes.
   *
   * @see LLVMBuilder::print
   */
  void dump();
  /**
   * @brief Print the llvm IR module into a stream
   */
  void print(llvm::raw_fd_ostream& s);
  /**
   * @brief get a type info struct type
   */
  llvm::StructType* getTypeInfoType();
  /**
   * @brief Start the codegen process
   *
   * Transform the value tree into a LLVM module
   * that can then be compiled to many more things.
   */
  void codegen() override;
  /**
   * @brief It executes the built in LLVM-IR optimization passes into
   * the resultant module
   * @note If the optimization level has been to '0', it will obiously
   * will not execute those optimization passes
   */
  void optimizeModule();
  /**
   * @brief Compile the LLVM-IR code into an object file into the
   * desired file.
   */
  int emitObjectFile(std::string out, bool log, bool object = true);
  /**
   * @brief It builds a value as an expression.
   * @param v Value to build
   */
  llvm::Value* expr(ir::Value* v) {
    this->ctx->doNotLoadInMemory = false;
    return load(build(v), v->getType());
  }

  // mark: build functions
  using AcceptorExtend::AcceptorExtend;

#define VISIT(n) void visit(ir::n*) override;
#include "../../defs/visits.def"
#undef VISIT

private:
  /**
   * @brief Create a new LLVM module
   * @return An unique ptr to a new module
   */
  std::unique_ptr<llvm::Module> newModule();
  /**
   * @brief Utility function to create a new LLVM module context
   * @return An unique pointer to the new context.
   */
  void newContext();
  /**
   * It loads a value if it's a pointer type.
   * @param v Value to load
   * @param ty Type to load
   * @return llvm::Value* Resultant llvm value
   */
  llvm::Value* load(llvm::Value* v, types::Type* ty);
  /**
   * Helper function to create a new function declaration
   *
   * @param fn Function value to generate
   * @return llvm::Function* Resultant llvm function
   */
  llvm::Function* createLLVMFunction(ir::Func* fn);
  /**
   * @brief It converts a value into a boolean value
  */
  llvm::Value* toBool(llvm::Value* v, bool isSigned = false);
  /**
   * @brief Transform a built in snowball type
   * to an llvm type.
   */
  llvm::Type* getLLVMType(types::Type* t, bool translateVoid = false);
  /**
   * @brief Fetch the C stdlib printf function
   */
  llvm::Function* getPrintfFunction();
  /**
   * @brief A allocates a new object inside the LLVM IR code and cast
   * it into the desired type.
   */
  llvm::Value* allocateObject(types::DefinedType* ty);
  /**
   * @brief It creates a new struct type and a new constant struct
   * value for a virtual table for @param ty
   */
  llvm::GlobalVariable* createVirtualTable(types::BaseType* ty, llvm::StructType* vtableType);
  /**
   * @brief It generates intrinsic functions for a given function call.
   * @param call The function call to generate the intrinsic function for.
   * @return true if the intrinsic function was generated successfully,
   */
  bool buildIntrinsic(ir::Call* call);
  /**
   * @brief It creates a new enum type and a new constant struct
   * value for a virtual table for @param call
   */
  llvm::Value* createEnumInit(ir::Call* call);
  /**
   * @brief It creates a new enum field type
   * @param ty The enum type
   * @param field The enum field
   */
  llvm::Type* createEnumFieldType(types::EnumType* ty, std::string field);
  /**
   * @brief Get llvm corresponding function type from an
   * already generate snowball type.
   */
  llvm::FunctionType* getLLVMFunctionType(types::FunctionType* fn, const ir::Func* func = nullptr);
  /**
   * @brief It creates a new vtable type for a given type.
   */
  llvm::StructType* getVtableType(types::BaseType* ty);
  /**
   * @brief Generate a bodied function. Notes: bodied
   * functions will have it's own scope meaning that we
   * cant get any variables from this function after it
   * has been generated. Also take note that this function
   * does not declare a new one, it just declares it's body.
   * thats why we need @param llvmFn as an already declared
   * llvm function.
   */
  llvm::Function* buildBodiedFunction(llvm::Function* llvmFn, ir::Func* fn);
  /**
   * @brief Set a "personality" function attached to a snowball
   *  generated function.
   *
   *  Personality functions can be really helpful in order to
   *  implement an throw/catch exception runtime.
   */
  void setPersonalityFunction(llvm::Function* func);
  /**
   * @brief It generates the test functions for the current module.
   */
  void createTests(llvm::Function* mainFunction);
  /**
   * @brief It generates the benchmark functions for the current module.
   */
  void createBenchmark(llvm::Function* mainFunction);
  /**
   * @brief It generates a function call or an invoke instruction
   * depending on the current context.
   */
  llvm::Value* createCall(llvm::FunctionType* ty, llvm::Value* callee, llvm::ArrayRef<llvm::Value*> args);
  /**
   * @brief It generates the LLVM IR contents that the user has
   *  manually inserted by using "inline LLVM".
   */
  llvm::Function* buildLLVMFunction(llvm::Function* llvmFn, ir::Func* fn);
  /**
   * @brief Builds an operator call.
   *
   * @param call The IR call instruction to build.
   * @return true if the operator was built successfully, false
   * otherwise.
   *
   * This function builds an operator call using the given IR call
   * instruction. It returns true if the operator was built
   * successfully and false otherwise.
   */
  bool buildOperator(ir::Call* call);
  /**
   * @brief Get a wrapper for a function. Subprogram is considered
   * also as a function description.
   *
   * from the llvm docs:
   *  > llvm::DISubprogram
   *  > This is a wrapper for a subprogram
   */
  llvm::DISubprogram* getDISubprogramForFunc(ir::Func* fn);
  /**
   * Add a global variable to the program.
   *
   * This function adds the specified variable declaration to the
   * global scope of the program. The variable can be accessed from
   * any function within the program.
   *
   * @param var A shared pointer to the variable declaration to add.
   * @param ty The type of the variable, or nullptr if the type should
   */
  void addGlobalVariable(std::shared_ptr<ir::VariableDeclaration> var, types::DefinedType* ty = nullptr);
  /**
   * Get the global constructor function.
   *
   * This function returns a pointer to the global constructor
   * function for the current LLVM module. The global constructor is a
   * special function that is called automatically when the program
   * starts up, before the main function is called. The global
   * constructor is typically used to initialize global variables or
   * perform other initialization tasks that need to happen before the
   * program can start running.
   *
   * @return A pointer to the global constructor function, or nullptr
   * if no such function exists in the current LLVM module.
   */
  llvm::Function* getGlobalCTOR(bool createIfNone = true);
  /**
   * @brief Get the "debug-information" equivalent of a snowball type.
   * @param ty type to convert for the debugger.
   */
  llvm::DIType* getDIType(types::Type* ty);
  /**
   * @brief LLVM wrapper to set a debug information
   *  location breakpoint
   */
  void setDebugInfoLoc(ir::Value* v);
  /**
   * Initialize a variable with a constant struct value.
   * @param var The variable to get the initializer for.
  */
  void initializeVariable(llvm::Value* var, llvm::Type* ty, unsigned int size);
  /**
   * @brief Creates (if it does not exist) or fetches a function
   * declaration used to allocate new bytes into memory.
   * @example This can be used to create a new instance of an object.
   */
  llvm::Function* getAllocaFunction();
  /**
   * @brief Creates (if it does not exist) or fetches a function
   * declaration used to throw an exception.
   */
  std::pair<llvm::FunctionType*, llvm::Function*> getThrowFunction();
  /**
   * @brief Creates a new instance of an exception.
   */
  llvm::Value* createException(llvm::Value* val, types::Type* type);
  /**
   * @brief It initializes the runtime. This function is called
   * before any other function is generated.
   */
  void initializeRuntime();
  /**
   * @brief Generate the current value given
   *
   * note: for the result of this function, `value`
   * can be accessed. This used instead of a return
   * value because c++ wants to make my life misserable.
   *
   * @note It may not return "value" if the value is a
   *  statement.
   */
  llvm::Value* build(ir::Value* v);
  /**
   * @brief Fetch the base type of a pointer type.
   * @param ty Pointer type to fetch the base type from.
   * @note if the type is not a pointer type, it will return the
   * same type.
   */
  types::Type* getBasePointerType(types::Type* ty) {
    if (auto x = utils::cast<types::ReferenceType>(ty)) return x->getBaseType();
    return ty;
  }
  /**
   * @brief It creates a name that can be used to reference an exported
   * function from another shared library.
   */
  std::string getSharedLibraryName(std::string name);
  /**
   * @brief Lambda function context struct type information
   */
  llvm::StructType* getLambdaContextType();
};

} // namespace codegen
} // namespace snowball

#endif // __SNOWBALL_LLVM_BUILDER_H_
