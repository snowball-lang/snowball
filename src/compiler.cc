#include <llvm/Support/CodeGen.h>
#include <llvm/Support/Host.h>
#include <llvm/Support/FileSystem.h>
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
#include <llvm/Support/FormattedStream.h>

#include <llvm/Transforms/IPO.h>
#include <llvm/IR/LegacyPassManager.h>

#include <llvm/Passes/OptimizationLevel.h>
#include <llvm/MC/TargetRegistry.h>
#include <llvm/Support/DynamicLibrary.h>

#include <llvm/Target/TargetMachine.h>
#include <llvm/Target/TargetOptions.h>

#include "llvm/Support/TargetSelect.h"

#include <llvm/Support/raw_ostream.h>
#include <llvm/ExecutionEngine/MCJIT.h>
// #include <llvm/ExecutionEngine/Orc/Legacy.h>
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

#include "snowball/types/Numbers.h"
#include "snowball/types/Void.h"
#include "snowball/types/String.h"
#include "snowball/types/Bool.h"

#include "snowball/llvm/gc.h"
#include "snowball/ld_args.h"

#include "snowball/attribs/tests.h"

#include <regex>
#include <string>
#include <stdio.h>
#include <unistd.h>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;
#define SN_MODULE_NAME "llvm_snowball_compile_mod_"

namespace snowball {
    Compiler::Compiler(std::string p_code, std::string p_path) {
        _code = p_code;
        _path = p_path;
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

        builder = std::make_shared<llvm::IRBuilder<>>(global_context);

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
        _module->setSourceFileName(_source_info->get_path());

        _enviroment = new Enviroment(_source_info);
        _initialized = true;

        config_folder = fs::current_path() / ".sn";
        if (!fs::exists(config_folder)) fs::create_directory(config_folder);
        if (!fs::exists(config_folder / "bin")) fs::create_directory(config_folder / "bin");
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

                SNAPI::Context api_context;
                api_context.is_test = _enabledTests;

                API = new SNAPI(std::move(this), api_context);

                SHOW_STATUS(Logger::compiling(Logger::progress(0.60)))
                link_std_classes();

                SHOW_STATUS(Logger::compiling(Logger::progress(0.70)))
                _generator = new Generator(
                    API,
                    _parser,
                    _enviroment,
                    _source_info,
                    builder,
                    _module.get(),
                    this->linked_libraries,
                    _enabledTests
                );

                for (auto* node : _parser->nodes()) {
                    _generator->generate(node);
                }

                SHOW_STATUS(Logger::compiling(Logger::progress(0.80)))

                for (auto attr : API->get_attributes()) {
                    attr->after_compile(API);
                }
                
                SHOW_STATUS(Logger::compiling(Logger::progress(0.85)))

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

            SHOW_STATUS(Logger::compiling(Logger::progress(1)))
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

    int Compiler::emit_binary(std::string p_output, bool p_pmessage) {
        // write to temporary object file
        std::string objfile = Logger::format("%s.so", p_output.c_str());
        DEBUG_CODEGEN("Emitting object file... (%s)", objfile.c_str());
        int objstatus = emit_object(objfile, false);
        if(objstatus != EXIT_SUCCESS) return objstatus;

        // object file written, now invoke llc
        // int ldstatus = execl(LD_PATH, "", NULL);
        std::string ldcommand; std::string p_input = Logger::format("%s.so", p_output.c_str());
        std::vector<std::string> ld_args = LD_ARGS();

        for(int i = 0; i < ld_args.size(); i++) { ldcommand += ld_args[i]; ldcommand += " "; }
        for(int i = 0; i < linked_libraries.size(); i++) {
            ldcommand += "-l:" + linked_libraries[i] + " ";
            DEBUG_CODEGEN("Linking library: %s", linked_libraries[i].c_str());
        }

        #if _SNOWBALL_CODEGEN_DEBUG
        ldcommand += "--verbose ";
        #endif

        ldcommand += " -o";
        ldcommand += p_output;

        DEBUG_CODEGEN("Invoking linker (" LD_PATH " with stdlib at " STATICLIB_DIR ")");
        DEBUG_CODEGEN("Linker command: %s", ldcommand.c_str());

        int ldstatus = system(ldcommand.c_str());
        if(ldstatus)
        {
            remove(objfile.c_str());
            throw SNError(IO_ERROR, Logger::format("Linking error. Linking with " LD_PATH " failed with code %d", ldstatus));
        }

        if (p_pmessage)
            Logger::success(Logger::format("Snowball project file successfully compiled! 🥳", BGRN, RESET, p_output.c_str()));

        // clean up
        DEBUG_CODEGEN("Cleaning up object file... (%s)", objfile.c_str());
        remove(objfile.c_str());

        return EXIT_SUCCESS;
    }

    int Compiler::emit_object(std::string p_output, bool p_pmessage) {

        // TODO: https://stackoverflow.com/questions/11657529/how-to-generate-an-executable-from-an-llvmmodule
        std::error_code EC;
        llvm::raw_fd_ostream dest(p_output, EC, llvm::sys::fs::OF_None);

        if (EC) {
            throw SNError(Error::IO_ERROR, Logger::format("Could not open file: %s", EC.message().c_str()));
        }

        llvm::legacy::PassManager pass;
        auto FileType = llvm::CGFT_ObjectFile;

        if (_target_machine->addPassesToEmitFile(pass, dest, nullptr, FileType)) {
            remove(p_output.c_str());
            throw SNError(Error::LLVM_INTERNAL, "TargetMachine can't emit a file of this type");
        }

        if (p_pmessage)
            Logger::success(Logger::format("Snowball project compiled to an object file! ✨\n", BGRN, RESET, p_output.c_str()));

        pass.run(*_module);
        dest.flush();

        return EXIT_SUCCESS;
    }

    toml::parse_result Compiler::get_config() {
        std::string name = fs::current_path() / "sn.toml";
        std::ifstream f(name.c_str());
        if (f.good()) {
            return toml::parse_file(name);
        }

        throw SNError(Error::IO_ERROR, Logger::format("Project configuration not found (%s)\n%shelp%s: try runing 'snowball init --cfg'", name.c_str(), BGRN, RESET));
    }

    int Compiler::execute(std::string p_output) {
        throw SNError(Error::TODO, "Execute from executable");
    }

    void Compiler::optimize() {
        llvm::LoopAnalysisManager loop_analysis_manager;
        llvm::FunctionAnalysisManager function_analysis_manager;
        llvm::CGSCCAnalysisManager c_gscc_analysis_manager;
        llvm::ModuleAnalysisManager module_analysis_manager;

        // Create the new pass manager builder.
        // Take a look at the PassBuilder constructor parameters for more
        // customization, e.g. specifying a TargetMachine or various debugging
        // options.
        llvm::PassBuilder pass_builder;

        // Register all the basic analyses with the managers.
        pass_builder.registerModuleAnalyses(module_analysis_manager);
        pass_builder.registerCGSCCAnalyses(c_gscc_analysis_manager);
        pass_builder.registerFunctionAnalyses(function_analysis_manager);
        pass_builder.registerLoopAnalyses(loop_analysis_manager);

        // cross register them too?
        pass_builder.crossRegisterProxies(loop_analysis_manager, function_analysis_manager,
                                        c_gscc_analysis_manager, module_analysis_manager);

        // todo: let user decide
        // llvm::OptimizationLevel level;
        // switch(_opt_level)
        // {
        //     case OPTIMIZE_O0: level = llvm::OptimizationLevel::O0; break;
        //     case OPTIMIZE_O1: level = llvm::OptimizationLevel::O1; break;
        //     case OPTIMIZE_O2: level = llvm::OptimizationLevel::O2; break;
        //     case OPTIMIZE_O3: level = llvm::OptimizationLevel::O3; break;
        //     case OPTIMIZE_Os: level = llvm::OptimizationLevel::Os; break;
        //     case OPTIMIZE_Oz: level = llvm::OptimizationLevel::Oz; break;
        //     default: THROW_INTERNAL_ERROR("during code optimization");
        // }
        llvm::ModulePassManager MPM = pass_builder.buildPerModuleDefaultPipeline(llvm::OptimizationLevel::O3);
        MPM.run(*_module.get(), module_analysis_manager);
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

        register_void(API);
        register_string(API);
        register_number(API);
        register_bool(API);

        API->register_all();

        API->register_attribute(new TestsAttribute());
    }

    void Compiler::create_source_info() {
        SourceInfo* source_info = new SourceInfo(_code, _path);
        _source_info = source_info;
    }
}
