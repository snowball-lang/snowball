

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

#include "snowball/lexer.h"
#include "snowball/compiler.h"

#include <regex>
#include <string>

#define SN_MODULE_NAME "llvm_snowball_compile_mod_"

namespace snowball {
    Compiler::Compiler(std::string p_code, std::string p_path) { _code = p_code                 ; _path = p_path              ; }
    Compiler::Compiler(const char* p_code, std::string p_path) { _code = std::string(p_code)    ; _path = p_path              ; }
    Compiler::Compiler(std::string p_code, const char* p_path) { _code = p_code                 ; _path = std::string(p_path) ; }
    Compiler::Compiler(const char* p_code, const char* p_path) { _code = std::string(p_code)    ; _path = std::string(p_path) ; }

    std::string Compiler::prepare_module_name() {
        std::string tmp = _path;
        std::string name = SN_MODULE_NAME + std::regex_replace(tmp, std::regex("\\W"), "_");

        return name;
    }

    void Compiler::initialize() {

        create_source_info();

        _module = std::make_unique<llvm::Module>(prepare_module_name(), _global_context);;
        llvm::verifyModule(*_module);

        _builder = std::make_unique<llvm::IRBuilder<>>(_global_context);

        _initialized = true;
    }

    void Compiler::compile() {
        if (!_initialized) {
            // TODO: error
        }

        _lexer = new Lexer(_source_info);
        _lexer->tokenize();

        _parser = new Parser(_lexer, _source_info);
        _parser->parse();

        _generator = new Generator(_parser, _source_info);

        _module->print(llvm::errs(),nullptr,false,true);
        _module.reset();
    }

    void Compiler::create_source_info() {
        SourceInfo* source_info = new SourceInfo(_code, _path);
        _source_info = source_info;
    }
}
