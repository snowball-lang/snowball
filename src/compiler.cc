#include <llvm-c-10/llvm-c/Target.h>
#include <llvm/IR/Module.h>
#include <llvm/ADT/SmallVector.h>
#include <llvm/IR/Verifier.h>
#include <llvm/IR/IRPrintingPasses.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/CallingConv.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/GlobalVariable.h>
#include <llvm/IR/InlineAsm.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/Passes/PassBuilder.h>
#include <llvm/Support/MathExtras.h>
#include <llvm/Support/FormattedStream.h>

#include <llvm/Target/TargetMachine.h>
#include <llvm/Target/TargetOptions.h>

#include "llvm/Support/TargetSelect.h"

#include <llvm/ExecutionEngine/MCJIT.h>
#include <llvm/ExecutionEngine/JITSymbol.h>

#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/Support/DynamicLibrary.h>

#include "snowball/api.h"
#include "snowball/types.h"
#include "snowball/lexer.h"
#include "snowball/compiler.h"
#include "snowball/generator.h"

#include "snowball/utils/utils.h"
#include "snowball/utils/mangle.h"

#include "snowball/types/Number.h"
#include "snowball/types/String.h"
#include "snowball/types/Bool.h"

#include "snowball/llvm/gc.h"

#include <regex>
#include <string>
#include <stdio.h>


//
// The adventures of a compiler.
//
// The snowball compiler can be separated into 2 sections. The front end and the backend.
//
// The front-end is used to recieve / tokenize and parse the source code. The source
// code is the used as an AST. The Generator (backend) is in charge of translating
// the AST into LLVM IR by using the LLVM API.
//
// The LLVM IR is can then be used for 2 situations. It can either be JITed by LLVM JIT
// or it can be compiled to an executable.
//
// There are helper services / utils to make snowball better called middlewares. Examples
// of this are:
//   The Enviroment
//   The Error Handling
// and many more. The utils do not appear in the diagram below because they are not as important.
// such as Loggers and string utils.
//
// Finally, the built in types are inserted via the Snowball API. The functions are declared into
// the LLVM IR and the mangled name would be used as a symbol pointing to the desired function. Another
// option is to generate the function via the LLVM API, this would be helpfull to do things like generic functions.
//
// ┌──────────────────────────────────────────────────────────────────────────────┐
// │                                                                              │
// │    ┌──────────────────────────────────────────────────────────────────────┐  │
// │    │                                                                      │  │
// │    │   Front End                                                          │  │
// │    │                                                                      │  │
// │    │ ─────────────────────────────────────────────────────────────────    │  │
// │    │                                                                      │  │    ┌────────────────────────────────────────────────────────────────────────┐
// │    │                                                                      │  │    │                                                                        │
// │    │  ┌─────────────────────────┐          ┌──────────────────────────┐   │  │    │  ┌─────────────────────────────────────────────────────────────────┐   │
// │    │  │                         │          │                          ├───┼──┘    │  │                                                                 │   │
// │    │  │  MAIN PROGRAM (AKA CLI) │          │  Tokenizer (AKA LEXER)   │   │       │  │   Back End                                                      │   │
// │    │  │                         │          │                          │   │       │  │                                                                 │   │
// │    │  │                         │          │                          │   │       │  │ ────────────────────────────────────────────────────────────────┤   │
// │    │  │ ┌───────┐    ┌────────┐ │          │                          │   │       │  │                                                                 │   │
// │    │  │ │REPL   │    │CODE    │ │          │                          │   │       │  │  ┌────────────────────────────┐  ┌───────────────────────────┐  │   │
// │    │  │ │       │    │FROM    │ │          │                          │   │       │  │  │                            │  │                           │  │   │
// ├────┼──┤ │       │ OR │FILE    │ │    ┌─────┼──────────────┐           │   │       │  │  │  GENERATOR                 │  │                           │  │   │
// │    │  │ │       │    │        │ │    │     │              │           │   │       │  │  │                            │  │                           │  │   │
// │    │  │ │       │    │        │ │    │     │    ┌─────────▼───────┐   │   │       └──┼──┤  ┌────────────────────┐    │  │                           │  │   │
// │    │  │ │       │    │        │ │    │     │    │                 │   │   │          │  │  │                    │    │  │                           │  │   │
// │    │  │ │       │    │        │ │    │     │    │                 │   │   │          │  │  │  GENERTION PROCESS ├────┼──►                           │  │   │
// │    │  │ └───┬───┘    └───┬────┘ │    │     │    │                 │   │   │          │  │  │                    │    │  │                           │  │   │
// │    │  │     │            │      │    │     │    │                 │   │   │          │  │  │  src/generator.cc  │    │  │         ENVIROMENT        ├──┼───┤
// │    │  │     └────────────┴──────┼────┘     │    │  TOKENIZING     │   │   │          │  │  │                    ◄────┼──┤                           │  │   │
// │    │  │      CODE AS STRING     │          │    │  PROCESS        │   │   │          │  │  │                    │    │  │                           │  │   │
// │    │  └─────────────────────────┘          │    │                 │   │   │          │  │  │                    │    │  │                           │  │   │
// │    │                                       │    │                 │   │   │          │  │  │                    │    │  │                           │  │   │
// │    │  ┌─────────────────────────┐          │    │                 │   │   │          │  │  │                    │    │  │                           │  │   │
// │    │  │                         │          │    │                 │   │   │          │  │  │                    │    │  │                           │  │   │
// │    │  │                         │          │    │                 │   │   │          │  │  │                    │    │  │                           │  │   │
// ├────┼──┤  PARSER                 │          │    │  src/lexer.cc   │   │   │          │  │  │                    │    │  │                           │  │   │
// │    │  │                         │          │    │                 │   │   │          │  │  │                    │    │  └───────────────────────────┘  │   │
// │    │  │                         │          │    │                 │   │   │          │  │  │                    │    │                                 │   │
// │    │  │  ┌──────────────────┐   │          │    │                 │   │   │          │  │  │                    ├─┐  │  ┌───────────────────────────┐  │   │
// │    │  │  │                  │   │          │    │                 │   │   │          │  │  │                    │ │  │  │                           │  │   │
// │    │  │  │ PARSING PROCESS  │   │          │    │                 │   │   │          │  │  │                    │ │  │  │                           │  │   │
// │    │  │  │                  │   │          │    └──────────┬──────┘   │   │          │  │  └─────────▲──────────┘ │  │  │                           │  │   │
// │    │  │  │                  │   │          │               │          │   │          │  │            │            │  │  │                           │  │   │
// │    │  │  │ src/parser.cc    │   │          │               │          │   │          │  │            │            │  │  │                           │  │   │
// │    │  │  │                  ◄───┼──────────┼───────────────┘          │   │          │  │            │            │  │  │                           │  │   │
// │    │  │  │                  │   │          │ TOKEN OBJECTS            │   │          │  │            │            └──┼──►          LLVM IR          ├──┼───┤
// │    │  │  │                  │   │          │                          │   │          │  │            │               │  │                           │  │   │
// │    │  │  │                  │   │          │                          │   │          │  │            │               │  │                           │  │   │
// │    │  │  │                  │   │          │                          │   │          │  │            │               │  │                           │  │   │
// │    │  │  └────────┬─────────┘   │          │                          │   │          │  │            │               │  │                           │  │   │
// │    │  │           │             │          │                          │   │          │  │            │               │  │                           │  │   │
// │    │  │           │             │          │                          │   │          │  │            │               │  │                           │  │   │
// │    │  └───────────┼─────────────┘          └──────────────────────────┘   │          │  └────────────┼───────────────┘  └─────────────┬─────────────┘  │   │
// │    │              │                                                       │          │               │                                │                │   │
// │    └──────────────┼───────────────────────────────────────────────────────┘          └───────────────┼────────────────────────────────┼────────────────┘   │
// │                   │                                                                                  │                                │                    │
// │                   └──────────────────────────────────────────────────────────────────────────────────┘                                │                    │
// │                                                                                                                                       │                    │
// │                                                    ┌──────────────────────────────────┐                                               │                    │
// │                                                    │                                  │                                               │                    │
// │                                                    │                                  │              ┌────────────────┐               │                    │
// │                                                    │                                  │              │                │               │                    │
// │                                                    │                                  │              │  OUTPUT:       │               │                    │
// └────────────────────────────────────────────────────►          ERROR HANDLER           │              │                ◄───────────────┘                    │
//                                                      │                                  │              │  LLVM JIT      │                                    │
//                                                      │                                  │              │  OR            │                                    │
//                                                      │                                  │              │  EXECUTABLE    │                                    │
//                                                      │                                  │              │                │                                    │
//                                                      └────────────────▲─────────────────┘              └────────────────┘                                    │
//                                                                       │                                                                                      │
//                                                                       └──────────────────────────────────────────────────────────────────────────────────────┘

#define SN_MODULE_NAME "llvm_snowball_compile_mod_"

#define NEW_IR_BUILDER() llvm::IRBuilder<> builder(global_context);
#define ADD_GLOBAL_IF_FN_EXISTS(name, function) \
    if (_module.get()->getFunction(name)) \
        executionEngine->addGlobalMapping(*_enviroment->get(name, nullptr)->llvm_function, function);

namespace snowball {
    Compiler::Compiler(std::string p_code, std::string p_path) : builder(llvm::IRBuilder<> (global_context)) { _code = p_code                 ; _path = p_path              ; NEW_IR_BUILDER() }
    Compiler::Compiler(const char* p_code, std::string p_path) : builder(llvm::IRBuilder<> (global_context)) { _code = std::string(p_code)    ; _path = p_path              ; NEW_IR_BUILDER() }
    Compiler::Compiler(std::string p_code, const char* p_path) : builder(llvm::IRBuilder<> (global_context)) { _code = p_code                 ; _path = std::string(p_path) ; NEW_IR_BUILDER() }
    Compiler::Compiler(const char* p_code, const char* p_path) : builder(llvm::IRBuilder<> (global_context)) { _code = std::string(p_code)    ; _path = std::string(p_path) ; }

    std::string Compiler::prepare_module_name() {
        std::string tmp = _path;
        std::string name = SN_MODULE_NAME + std::regex_replace(tmp, std::regex("\\W"), "_");

        return name;
    }

    void Compiler::initialize() {


        llvm::InitializeNativeTarget();
        llvm::InitializeAllTargetInfos();
        llvm::InitializeAllTargets();
        llvm::InitializeAllTargetMCs();
        llvm::InitializeAllAsmPrinters();
        LLVMInitializeNativeAsmParser();
        create_source_info();

        _module = std::make_unique<llvm::Module>(prepare_module_name(), global_context);

        _enviroment = new Enviroment(_source_info);

        _initialized = true;
    }

    void Compiler::compile() {
        if (!_initialized) {
            throw SNError(Error::COMPILER_ERROR, "Compiler has not been initialized!");
        }

        /* ignore_goto_errors() */ {
            std::string llvm_error;

            _lexer = new Lexer(_source_info);
            _lexer->tokenize();

            if (_lexer->tokens.size() != 0) {
                _parser = new Parser(_lexer, _source_info);
                _parser->parse();

                API = new SNAPI(std::move(this));
                Generics* generics_api = new Generics(std::move(this));

                link_std_classes();

                _generator = new Generator(
                    API,
                    _parser,
                    _enviroment,
                    _source_info,
                    std::move(builder),
                    _module.get(),
                    _testing_context,
                    generics_api,
                    _enabledTests
                );

                for (auto* node : _parser->nodes()) {
                    _generator->generate(node);
                }
            }

            llvm::sys::DynamicLibrary::LoadLibraryPermanently(nullptr);

            #if _SNOWBALL_CAN_OPTIMIZE
            optimize();
            #endif

            std::string module_error_string;
            llvm::raw_string_ostream module_error_stream(module_error_string);
            llvm::verifyModule(*_module, &module_error_stream);

            if (!module_error_string.empty())
                throw SNError(Error::LLVM_INTERNAL, module_error_string);


            #if _SNOWBALL_BYTECODE_DEBUG

                PRINT_LINE("Bytecode:")
                PRINT_LINE(LINE_SEPARATOR)
                _module->print(llvm::outs(), nullptr);
                PRINT_LINE(LINE_SEPARATOR)

            #endif
        }
    }

    int Compiler::execute() {
        std::string llvm_error;

        llvm::ExecutionEngine *executionEngine = llvm::EngineBuilder(std::move(_module))
                                                .setErrorStr(&llvm_error)
                                                .setEngineKind(llvm::EngineKind::JIT)
                                                .create();

        if (!llvm_error.empty())
            throw SNError(Error::LLVM_INTERNAL, llvm_error);

        if (_enabledTests) {
            int test_success = 1;

            // todo: if it is a folder/import, iterate all paths
            if (_testing_context->getTestLength() == 0) {
                Logger::warning("No unit tests found!");
                return 2;
            }

            Logger::log(Logger::format("    [%s]", _path.c_str()));

            for (int i = 0; i < _testing_context->getTestLength(); i++) {
                Logger::rlog(Logger::format("        %s%s%s (%i)... ", BBLU, _testing_context->getTestAt(i).c_str(), RESET, i + 1));

                snowball_int_t (*function)() = reinterpret_cast<snowball_int_t (*)()>(executionEngine->getFunctionAddress(_testing_context->get_name(i+1)));
                snowball_int_t result = function();

                if (!result) {
                    test_success = 0;
                    Logger::log(Logger::format("%sFAILED%s", BRED, RESET));
                    break;
                } else if (result == 1) {
                    Logger::log(Logger::format("%sPASSED%s", BGRN, RESET));
                } else if (result == 2) {
                    Logger::log(Logger::format("%sSKIPED%s", BYEL, RESET));
                } else {
                    Logger::log(Logger::format("%sUNKNOWN%s", BBLK, RESET));
                }
            }

            return test_success;
        } else {
            llvm::Function *main_fn = executionEngine->FindFunctionNamed(llvm::StringRef(mangle(_SNOWBALL_FUNCTION_ENTRY, {}, false)));
            executionEngine->runFunction(main_fn, {});
            return 0; // TODO: return function result
        }
    }

    void Compiler::optimize() {
        llvm::LoopAnalysisManager LAM;
        llvm::FunctionAnalysisManager FAM;
        llvm::CGSCCAnalysisManager CGAM;
        llvm::ModuleAnalysisManager MAM;

        // Create the new pass manager builder.
        // Take a look at the PassBuilder constructor parameters for more
        // customization, e.g. specifying a TargetMachine or various debugging
        // options.
        llvm::PassBuilder PB;

        // Register all the basic analyses with the managers.
        PB.registerModuleAnalyses(MAM);
        PB.registerCGSCCAnalyses(CGAM);
        PB.registerFunctionAnalyses(FAM);
        PB.registerLoopAnalyses(LAM);
        PB.crossRegisterProxies(LAM, FAM, CGAM, MAM);

        // Create the pass manager.
        // This one corresponds to a typical -O2 optimization pipeline.
        llvm::ModulePassManager MPM = PB.buildPerModuleDefaultPipeline(llvm::PassBuilder::OptimizationLevel::O2);
        MPM.run(*_module.get(), MAM);
    }

    void Compiler::cleanup() {

        #if _SNOWBALL_SYMTABLE_DEBUG
        PRINT_LINE("Enviroment:")
        PRINT_LINE(LINE_SEPARATOR)

        _enviroment->debug();
        PRINT_LINE(LINE_SEPARATOR)
        #endif

        _module.reset();
    }

    void Compiler::link_std_classes() {
        API->init_mode();

        register_string(API);
        register_number(API);
        register_bool(API);

        API->register_all();
    }

    void Compiler::create_source_info() {
        SourceInfo* source_info = new SourceInfo(_code, _path);
        _source_info = source_info;
    }
}
