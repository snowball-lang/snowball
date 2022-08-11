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

#include <llvm/IR/LegacyPassManager.h>

#include <llvm/Support/TargetRegistry.h>
#include <llvm/Support/DynamicLibrary.h>

#include <llvm/Target/TargetMachine.h>
#include <llvm/Target/TargetOptions.h>

#include "llvm/Support/TargetSelect.h"

#include <llvm/ExecutionEngine/MCJIT.h>
#include <llvm/ExecutionEngine/JITSymbol.h>

#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>

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

#define SN_MODULE_NAME "llvm_snowball_compile_mod_"

#define NEW_IR_BUILDER() llvm::IRBuilder<> builder(global_context);
#define ADD_GLOBAL_IF_FN_EXISTS(name, function) \
    if (_module.get()->getFunction(name)) \
        executionEngine->addGlobalMapping(*_enviroment->get(name, nullptr)->llvm_function, function);

namespace snowball {
    Compiler::Compiler(std::string p_code, std::string p_path)
        : builder(llvm::IRBuilder<> (global_context)) {
            _code = p_code;
            _path = p_path;

            NEW_IR_BUILDER()
        }

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

        std::string target_error;

        auto targetTriple = llvm::sys::getDefaultTargetTriple();
        auto target = llvm::TargetRegistry::lookupTarget(targetTriple, target_error);

        if (!target) {
            throw new SNError(Error::LLVM_INTERNAL, Logger::format("Could not create target info: %s", target_error.c_str()));
        }

        auto CPU = "generic";
        auto features = "";

        llvm::TargetOptions opt;
        auto RM = llvm::Optional<llvm::Reloc::Model>();
        _target_machine = target->createTargetMachine(targetTriple, CPU, features, opt, RM);

        _module = std::make_unique<llvm::Module>(prepare_module_name(), global_context);

        _module->setDataLayout(_target_machine->createDataLayout());
        _module->setTargetTriple(targetTriple);

        _enviroment = new Enviroment(_source_info);

        _initialized = true;
    }

    void Compiler::compile(bool verbose) {
        if (!_initialized) {
            throw SNError(Error::COMPILER_ERROR, "Compiler has not been initialized!");
        }

        #define SHOW_STATUS(status) if (verbose) status;

        SHOW_STATUS(Logger::compiling(Logger::progress(0)));

        /* ignore_goto_errors() */ {
            std::string llvm_error;

            SHOW_STATUS(Logger::compiling(Logger::progress(0.30)))
            _lexer = new Lexer(_source_info);
            _lexer->tokenize();

            if (_lexer->tokens.size() != 0) {
                SHOW_STATUS(Logger::compiling(Logger::progress(0.50)))

                _parser = new Parser(_lexer, _source_info);
                _parser->parse();

                SHOW_STATUS(Logger::compiling(Logger::progress(0.55)))
                API = new SNAPI(*this);
                Generics* generics_api = new Generics(std::move(this));

                SHOW_STATUS(Logger::compiling(Logger::progress(0.60)))
                link_std_classes();

                SHOW_STATUS(Logger::compiling(Logger::progress(0.70)))
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

                SHOW_STATUS(Logger::compiling(Logger::progress(0.80)))
            }

            llvm::sys::DynamicLibrary::LoadLibraryPermanently(nullptr);

            #if _SNOWBALL_SYMTABLE_DEBUG
            PRINT_LINE("Enviroment:")
            PRINT_LINE(LINE_SEPARATOR)

            _enviroment->debug();
            PRINT_LINE(LINE_SEPARATOR)
            #endif

            #if _SNOWBALL_CAN_OPTIMIZE
            optimize();
            #endif

            std::string module_error_string;
            llvm::raw_string_ostream module_error_stream(module_error_string);
            llvm::verifyModule(*_module, &module_error_stream);

            if (!module_error_string.empty())
                throw SNError(Error::LLVM_INTERNAL, module_error_string);

            SHOW_STATUS(Logger::compiling(Logger::progress(0.1)))
            SHOW_STATUS(Logger::reset_status())

            #if _SNOWBALL_BYTECODE_DEBUG

                PRINT_LINE("Bytecode:")
                PRINT_LINE(LINE_SEPARATOR)
                _module->print(llvm::outs(), nullptr);
                PRINT_LINE(LINE_SEPARATOR)

            #endif
        }

        #undef SHOW_STATUS
    }

    void Compiler::emit_object(std::string p_output) {
        throw SNError(Error::TODO, "Object compilation is not yet ready!");

        // TODO: https://stackoverflow.com/questions/11657529/how-to-generate-an-executable-from-an-llvmmodule
        std::error_code EC;
        llvm::raw_fd_ostream dest(p_output, EC, llvm::sys::fs::OF_None);

        if (EC) {
            throw SNError(Error::IO_ERROR, Logger::format("Could not open file: %s", EC.message().c_str()));
        }

        llvm::legacy::PassManager pass;
        auto FileType = llvm::CGFT_ObjectFile;

        if (_target_machine->addPassesToEmitFile(pass, dest, nullptr, FileType)) {
            throw SNError(Error::LLVM_INTERNAL, "TargetMachine can't emit a file of this type");
        }

        pass.run(*_module);
        dest.flush();
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
