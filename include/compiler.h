
#include <string>

#include "lexer.h"
#include "parser.h"
#include "source_info.h"

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
