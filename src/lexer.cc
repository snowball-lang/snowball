
#include "lexer.h"
#include <string>

namespace snowball {
    Lexer::Lexer(SourceInfo* p_source_info) {
        _source_info = p_source_info;
    }

    void Lexer::tokenize() {
        Logger::verbose("hello");
    }

}
