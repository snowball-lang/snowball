
#include "../common.h"
#include "../lexer/tokens/token.h"
#include "../services/OperatorService.h"
#include "./Parser.h"

#include <assert.h>

namespace snowball::parser {

Syntax::Statement::TryCatch* Parser::parseTryCatch() {
    assert(is<TokenType::KWORD_TRY>());
    auto dbg = DBGSourceInfo::fromToken(m_source_info, m_current);
    next();
    consume<TokenType::BRACKET_LCURLY>("a left curly brace '{' to start the try block");
    auto tryBlock = parseBlock();
    next(); // We know it's a right curly brace, but we don't need to check it
    std::vector<Syntax::Statement::TryCatch::CatchBlock*> catchBlocks;
    assert_tok<TokenType::KWORD_CATCH>("a catch block");
    while (is<TokenType::KWORD_CATCH>()) {
        next();
        consume<TokenType::BRACKET_LPARENT>("a left parenthesis '(' to start the catch block");
        auto name = assert_tok<TokenType::IDENTIFIER>("an identifier for the exception variable").to_string();
        next();
        consume<TokenType::SYM_COLLON>("a collon ':' to separate the exception variable from the type");
        auto type = parseType();
        consume<TokenType::BRACKET_RPARENT>("a right parenthesis ')' to end the catch block header");
        auto block = parseBlock();
        catchBlocks.push_back(new Syntax::Statement::TryCatch::CatchBlock(type, name, block));
    }
    auto tryCatch = new Syntax::Statement::TryCatch(tryBlock, catchBlocks);
    tryCatch->setDBGInfo(dbg);
    return tryCatch;
}   

} // namespace snowball::parser
