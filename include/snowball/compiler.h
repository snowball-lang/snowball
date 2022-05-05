
#include <string>


#include "lexer.h"
#include "parser.h"
#include "source_info.h"

#include "llvm/IR/Module.h"

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

            // variables
            std::string _code;
            std::string _path;

            SourceInfo* _source_info;
            bool _initialized = false;

            Lexer* _lexer;
            Parser* _parser;

            // methods
            void create_source_info();
    };
}

#endif // __SNOWBALL_COMPILER_H_
