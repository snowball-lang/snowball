

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

#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/GenericValue.h>

#include "snowball/types.h"
#include "snowball/lexer.h"
#include "snowball/compiler.h"
#include "snowball/generator.h"

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
        llvm::verifyModule(*_module);

        _enviroment = new Enviroment();

        auto i32 = _builder.getInt32Ty();
        auto prototype = llvm::FunctionType::get(i32, false);
        llvm::Function *main_fn = llvm::Function::Create(prototype, llvm::Function::ExternalLinkage, "main", _module.get());
        llvm::BasicBlock *body = llvm::BasicBlock::Create(_global_context, "body", main_fn);
        _builder.SetInsertPoint(body);

        link_std_classes();

        _initialized = true;
    }

    void Compiler::compile() {
        if (!_initialized) {
            // TODO: error
        }

        _lexer = new Lexer(_source_info);
        _lexer->tokenize();

        if (_lexer->tokens.size() == 0) {
            goto cleanup;
            return;
        }

        _parser = new Parser(_lexer, _source_info);
        _parser->parse();

        _generator = new Generator(_parser, _enviroment, _source_info, std::move(_builder), _buildin_types);
        _generator->generate();

        goto cleanup;

cleanup:
        _builder.CreateRet(llvm::ConstantInt::get( llvm::Type::getInt32Ty( _global_context ), 0 ));

        _module->print(llvm::errs(),nullptr,false,true);
        _module.reset();
    }

    void Compiler::link_std_classes() {
        llvm::PointerType* i8p = _builder.getInt8PtrTy();

        auto sn_number_prototype = llvm::FunctionType::get(i8p, std::vector<llvm::Type *> { i8p }, false);
        auto sn_number_fn = llvm::Function::Create(sn_number_prototype, llvm::Function::ExternalLinkage, "create_number", _module.get());

        _buildin_types = {
            .sn_number_class = sn_number_fn
        };
    }

    void Compiler::create_source_info() {
        SourceInfo* source_info = new SourceInfo(_code, _path);
        _source_info = source_info;
    }
}
