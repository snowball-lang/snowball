
#include "../../../exec/cli.h"
#include "../../ValueVisitor/Visitor.h"
#include "../../ast/types/FunctionType.h"
#include "../../ir/id.h"
#include "../../ir/module/MainModule.h"
#include "../../ir/values/Func.h"
#include "../../ir/values/Value.h"

#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/IR/DIBuilder.h"
#include "llvm/IR/DebugInfoMetadata.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"

#include <cstdint>
#include <llvm-14/llvm/Target/TargetMachine.h>
#include <map>
#include <memory>

#ifndef __SNOWBALL_LLVM_BUILDER_H_
#define __SNOWBALL_LLVM_BUILDER_H_

namespace snowball {
namespace codegen {

/**
 * @brief Some context so that we can know
 * where in the program we are located.
 */
class LLVMBuilderContext {
    // Current function being generated
    ptr<llvm::Function> currentFunction = nullptr;

    // All variables used around the program.
    // note: all of the llvm values are actually
    // "alloca" instructions.
    std::map<ir::id_t, ptr<llvm::Value>> symbols;

  public:
    /// @return Current function being generated
    auto getCurrentFunction() { return currentFunction; }
    /// @return Change the current function to a new one
    void setCurrentFunction(ptr<llvm::Function> fn) { currentFunction = fn; }
    /// @brief Reset the current function to a null pointer
    void clearCurrentFunction() { currentFunction = nullptr; }

    /// @return A full list of symbols used around the program
    auto& getAllSymbols() { return symbols; }
    /// @return Add a new symbol to the symbol map
    void addSymbol(ir::id_t i, ptr<llvm::Value> s) { symbols.emplace(i, s); }
    /// @brief Get the corresponding symbol to an id
    auto getSymbol(ir::id_t i) -> ptr<llvm::Value> { return symbols.at(i); }
    /// @brief Clear the symbol table
    void clearSymbols() { return symbols.clear(); }

    // TODO: add a function to clear functions, symbols, etc as cleanup
};

/**
 * An instructions visitor that generates
 * llvm IR from our ir.
 */
class LLVMBuilder : AcceptorExtend<LLVMBuilder, ValueVisitor> {
    // A global map to keep track of all processed
    // functions.
    std::map<ir::id_t, ptr<llvm::Function>> funcs;
    // Some sort of cache to prevent struct-like types
    // from being generated over and over again.
    std::map<ir::id_t, ptr<llvm::Type>> types;
    // Internal module given by the internal representation
    // of the program.
    std::shared_ptr<ir::MainModule> iModule;

    // Context used all around the codegen process
    std::unique_ptr<LLVMBuilderContext> ctx =
        std::make_unique<LLVMBuilderContext>();

    /**
     * Struct containing all debug information
     * tools needed.
     */
    struct DebugInfo {
        /// Current compilation unit
        ptr<llvm::DICompileUnit> unit = nullptr;
        /// Debug info builder
        std::unique_ptr<llvm::DIBuilder> builder = nullptr;
        // Debug flag
        bool debug = false;

        // Create a new DIFile for llvm
        ptr<llvm::DIFile> getFile(const std::string& path);
    } dbg;

    /**
     * Helper struct that will allow us to create
     * certain types of llvm instructions.
     */
    struct {

        /**
         * Create a new llvm value.
         * @return Created llvm value.
         */
        template <typename Inst, class... Args>
        static ptr<Inst> create(Args&&...args) {
            return Inst::Create(std::forward<Args>(args)...);
        }

        /**
         * Create a new llvm instruction.
         * @return Created llvm struction.
         */
        template <typename Inst, class... Args>
        static ptr<Inst> insert(Args&&...args) {
            return new Inst(std::forward<Args>(args)...);
        }
    } h;

    // LLVM IR module that acts as a top level container of
    // all other LLVM Intermediate Representation (IR) objects
    std::unique_ptr<llvm::Module> module;
    // An unique pointer for an instruction builder.
    std::unique_ptr<llvm::IRBuilder<>> builder;
    // LLVM context for the module
    std::unique_ptr<llvm::LLVMContext> context;
    // Last compiled (generated) value
    ptr<llvm::Value> value;
    // Target machine that the module will be compiled into
    ptr<llvm::TargetMachine> target;

  public:
    // Create a new instance of a llvm builder
    LLVMBuilder(std::shared_ptr<ir::MainModule> mod);
    /**
     * @brief Dump the LLVM IR code to stdout.
     *
     * note: this must only be used for debug
     * purposes.
     */
    void dump();
    /**
     * @brief Start the codegen process
     *
     * Transform the value tree into a LLVM module
     * that can then be compiled to many more things.
     */
    void codegen() override;
    /**
     * @brief It executes the built in LLVM-IR optimization passes into the
     * resultant module
     * @note If the optimization level has been to '0', it will obiously will
     * not execute those optimization passes
     */
    void optimizeModule(exec::Options::Optimization o);
    /**
     * @brief Compile the LLVM-IR code into an object file into the desired
     *  file.
     */
    int emitObjectFile(std::string out, bool log);

    // mark: build functions
    using AcceptorExtend::AcceptorExtend;

#define VISIT(n) void visit(ptr<ir::n>) override;
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
     * Helper function to create a new function declaration
     *
     * @param fn Function value to generate
     * @return ptr<llvm::Function> Resultant llvm function
     */
    ptr<llvm::Function> createLLVMFunction(ptr<ir::Func> fn);
    /**
     * @brief Transform a built in snowball type
     * to an llvm type.
     */
    ptr<llvm::Type> getLLVMType(ptr<types::Type> t);
    /**
     * @brief A allocates a new object inside the LLVM IR code and cast it
     *  into the desired type.
     */
    ptr<llvm::Value> allocateObject(std::shared_ptr<types::DefinedType> ty);
    /**
     * @brief Utility function to the actual `getLLVMType`
     * function. This is just a workaround to avoid shared
     * pointers.
     */
    ptr<llvm::Type> getLLVMType(std::shared_ptr<types::Type> t);
    /**
     * @brief Get llvm corresponding function type from an
     * already generate snowball type.
     */
    ptr<llvm::FunctionType> getLLVMFunctionType(ptr<types::FunctionType> fn);
    /**
     * @brief Generate a bodied function. Notes: bodied
     * functions will have it's own scope meaning that we
     * cant get any variables from this function after it
     * has been generated. Also take note that this function
     * does not declare a new one, it just declares it's body.
     * thats why we need @param llvmFn as an already declared
     * llvm function.
     */
    void buildBodiedFunction(ptr<llvm::Function> llvmFn, ptr<ir::Func> fn);
    /**
     * @brief Get a wrapper for a function. Subprogram is considered
     * also as a function description.
     *
     * from the llvm docs:
     *  > llvm::DISubprogram
     *  > This is a wrapper for a subprogram
     */
    ptr<llvm::DISubprogram> getDISubprogramForFunc(ptr<ir::Func> fn);
    /**
     * @brief Get the "debug-information" equivalent of a snowball type.
     * @param ty type to convert for the debugger.
     */
    ptr<llvm::DIType> getDIType(ptr<types::Type> ty);
    /**
     * @brief LLVM wrapper to set a debug information
     *  location breakpoint
     */
    void setDebugInfoLoc(ptr<ir::Value> v);
    /**
     * @brief Creates (if it does not exist) or fetches a function declaration
     *  used to allocate new bytes into memory.
     * @example This can be used to create a new instance of an object.
     */
    ptr<llvm::Function> getAllocaFunction();
    /**
     * @brief Generate the current value given
     *
     * note: for the result of this function, `value`
     * can be accessed. This used instead of a return
     * value because c++ wants to make my life misserable.
     */
    ptr<llvm::Value> build(ptr<ir::Value> v) {
        setDebugInfoLoc(v);
        v->visit(this);
        return this->value;
    }
};

} // namespace codegen
} // namespace snowball

#endif // __SNOWBALL_LLVM_BUILDER_H_
