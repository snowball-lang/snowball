
#include <string>


#include "lexer.h"
#include "parser.h"
#include "generator.h"
#include "enviroment.h"
#include "source_info.h"

#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>

#ifndef __SNOWBALL_COMPILER_H_
#define __SNOWBALL_COMPILER_H_

namespace snowball {

    class Compiler {

        public:
            Compiler(std::string p_code, std::string p_path);
            Compiler(const char* p_code, std::string p_path);
            Compiler(std::string p_code, const char* p_path);
            Compiler(const char* p_code, const char* p_path);

            void initialize();
            void compile();

            ~Compiler() {};

        private:
            // llvm
            std::unique_ptr<llvm::Module> _module;
            llvm::LLVMContext _global_context;
            std::unique_ptr<llvm::IRBuilder<>> _builder;

            // variables
            std::string _code;
            std::string _path;

            SourceInfo* _source_info;
            bool _initialized = false;

            Lexer* _lexer;
            Parser* _parser;
            Generator* _generator;

            Enviroment* _enviroment;

            // methods
            void create_source_info();
            std::string prepare_module_name();
    };
}

#endif // __SNOWBALL_COMPILER_H_
