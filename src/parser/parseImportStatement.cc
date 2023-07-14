
#include "Parser.h"

#include <assert.h>

namespace snowball {
namespace parser {

Syntax::Statement::ImportStmt* Parser::parseImportStatement() {
    assert(is<TokenType::KWORD_IMPORT>());
    auto dbg = DBGSourceInfo::fromToken(m_source_info, m_current);

    next();

    std::string package = assert_tok<TokenType::IDENTIFIER>(
        "an identifier for package reference"
    ).to_string();
    next();

    consume<TokenType::SYM_COLCOL>("'::'");
    std::vector<std::string> paths;
    paths.push_back(assert_tok<TokenType::IDENTIFIER>("an identifier").to_string());
    next();

    while (is<TokenType::SYM_COLCOL>()) {
        next();
        if (is<TokenType::IDENTIFIER>()) {
            paths.push_back(m_current.to_string());
        } else if (is<TokenType::SYM_DOT>() && is<TokenType::SYM_DOT>(peek())) {
            paths.push_back("..");
        } else {
            prev();
            break;
        }

        next();
    }

    // TODO: handle all import types
    prev();
    auto import = Syntax::N<Syntax::Statement::ImportStmt>(paths, package);

    auto width = m_current.get_pos().second - dbg->pos.second;
    dbg->width = width;
    import->setDBGInfo(dbg);

    return import;
}

} // namespace parser
} // namespace snowball
