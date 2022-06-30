
#include <llvm/IR/Mangler.h>
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
#include <llvm/IR/Module.h>
#include <llvm/Support/FormattedStream.h>
#include <llvm/Support/MathExtras.h>

#include <llvm/Target/TargetMachine.h>

#include <llvm/ExecutionEngine/MCJIT.h>
#include <llvm/ExecutionEngine/JITSymbol.h>

#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>

#include "snowball/types.h"
#include "snowball/lexer.h"
#include "snowball/compiler.h"
#include "snowball/generator.h"

#include "snowball/types/Number.h"

#include <regex>
#include <string>

#define SN_MODULE_NAME "llvm_snowball_compile_mod_"

#define NEW_IR_BUILDER() llvm::IRBuilder<> _builder(_global_context);

namespace snowball {
    Compiler::Compiler(std::string p_code, std::string p_path) : _builder(llvm::IRBuilder<> (_global_context)) { _code = p_code                 ; _path = p_path              ; NEW_IR_BUILDER() }
    Compiler::Compiler(const char* p_code, std::string p_path) : _builder(llvm::IRBuilder<> (_global_context)) { _code = std::string(p_code)    ; _path = p_path              ; NEW_IR_BUILDER() }
    Compiler::Compiler(std::string p_code, const char* p_path) : _builder(llvm::IRBuilder<> (_global_context)) { _code = p_code                 ; _path = std::string(p_path) ; NEW_IR_BUILDER() }
    Compiler::Compiler(const char* p_code, const char* p_path) : _builder(llvm::IRBuilder<> (_global_context)) { _code = std::string(p_code)    ; _path = std::string(p_path) ; }

    std::string Compiler::prepare_module_name() {
        std::string tmp = _path;
        std::string name = SN_MODULE_NAME + std::regex_replace(tmp, std::regex("\\W"), "_");

        return name;
    }

    void Compiler::initialize() {
        LLVMInitializeNativeTarget();
        LLVMInitializeNativeAsmParser();
        LLVMInitializeNativeAsmPrinter();

        create_source_info();

        _module = std::make_unique<llvm::Module>(prepare_module_name(), _global_context);;

        _enviroment = new Enviroment(_source_info);

        link_std_classes();

        _initialized = true;
    }

    void Compiler::compile() {
        if (!_initialized) {
            // TODO: error
        }

        /* ignore_goto_errors() */ {
            std::string llvm_error;

            _lexer = new Lexer(_source_info);
            _lexer->tokenize();

            if (_lexer->tokens.size() != 0) {
                _parser = new Parser(_lexer, _source_info);
                _parser->parse();

                _generator = new Generator(_parser, _enviroment, _source_info, std::move(_builder), _module.get(), _buildin_types);

                for (auto node : _parser->nodes()) {
                    _generator->generate(node);
                }
            }

            std::string module_error;
            llvm::raw_string_ostream module_stream(module_error);
            llvm::verifyModule(*_module, &module_stream);

            if (!module_error.empty())
                throw SNError(Error::LLVM_INTERNAL, module_error);

            _module->print(llvm::outs(), nullptr);
            printf("\n\n------------------\n");

            // TODO: move to Compiler::execute()
            llvm::ExecutionEngine *executionEngine = llvm::EngineBuilder(std::move(_module))
                                                    .setErrorStr(&llvm_error)
                                                    .setEngineKind(llvm::EngineKind::JIT)
                                                    .create();

            if (!llvm_error.empty())
                throw SNError(Error::LLVM_INTERNAL, llvm_error);

            // TODO: move into a function
            executionEngine->addGlobalMapping(_buildin_types.sn_number_class, reinterpret_cast<snowball::Number*>(&Number_create));
            executionEngine->addGlobalMapping(_buildin_types.sn_number__sum, reinterpret_cast<snowball::Number*>(&Number__sum));

            llvm::Function *main_fn = executionEngine->FindFunctionNamed(llvm::StringRef("main"));
            auto result = executionEngine->runFunction(main_fn, {});
        }

        goto cleanup;

cleanup:
        _module.reset();
    }

    void Compiler::link_std_classes() {
        std::string llvm_error;
        llvm::raw_string_ostream message_stream(llvm_error);

        llvm::PointerType* i8p = _builder.getInt8PtrTy();
        llvm::Type* nt = get_llvm_type_from_sn_type(BuildinTypes::NUMBER, _builder);

        /* Number */
        auto sn_number_prototype = llvm::FunctionType::get(i8p, std::vector<llvm::Type *> { nt }, false);
        auto sn_number_fn = llvm::Function::Create(sn_number_prototype, llvm::Function::ExternalLinkage, "Number_create", _module.get());

        auto sn_number_sum_prototype = llvm::FunctionType::get(i8p, std::vector<llvm::Type *> { i8p, nt }, false);
        auto sn_number_add_fn = llvm::Function::Create(sn_number_sum_prototype, llvm::Function::ExternalLinkage, "Number__sum", _module.get());

        llvm::verifyFunction(*sn_number_fn, &message_stream);
        llvm::verifyFunction(*sn_number_add_fn, &message_stream);

        if (!llvm_error.empty())
            throw SNError(Error::LLVM_INTERNAL, llvm_error);

        _buildin_types = {
            .sn_number_class = sn_number_fn,
            .sn_number__sum = sn_number_add_fn
        };
    }

    void Compiler::create_source_info() {
        SourceInfo* source_info = new SourceInfo(_code, _path);
        _source_info = source_info;
    }
}
