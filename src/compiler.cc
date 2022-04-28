
#include "lexer.h"
#include "compiler.h"

#include <string>

namespace snowball {
    Compiler::Compiler(std::string p_code, std::string p_path) { _code = p_code                 ; _path = p_path              ; }
    Compiler::Compiler(const char* p_code, std::string p_path) { _code = std::string(p_code)    ; _path = p_path              ; }
    Compiler::Compiler(std::string p_code, const char* p_path) { _code = p_code                 ; _path = std::string(p_path) ; }
    Compiler::Compiler(const char* p_code, const char* p_path) { _code = std::string(p_code)    ; _path = std::string(p_path) ; }

    void Compiler::initialize() {

        create_source_info();

        _initialized = true;
    }

    void Compiler::compile() {
        if (!_initialized) {
            // TODO: error
        }

        _lexer = new Lexer(_source_info);
        _lexer->tokenize();
    }

    void Compiler::create_source_info() {
        SourceInfo* source_info = new SourceInfo(_code, _path);
        _source_info = source_info;
    }
}
