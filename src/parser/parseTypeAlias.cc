
#include "../common.h"
#include "../services/OperatorService.h"
#include "../token.h"
#include "./Parser.h"

#include <assert.h>

namespace snowball::parser {

Syntax::Statement::TypeAlias* Parser::parseTypeAlias() {
    assert(is<TokenType::KWORD_TYPEDEF>());
    next(); // East "class"

    bool isPublic = false;
    if (is<TokenType::KWORD_PUBLIC, TokenType::KWORD_PRIVATE>(peek(-3, true))) {
        isPublic = is<TokenType::KWORD_PUBLIC>(peek(-3, true));
    }

    auto name = assert_tok<TokenType::IDENTIFIER>("class identifier").to_string();
    auto dbg = DBGSourceInfo::fromToken(m_source_info, m_current);
    Syntax::Statement::GenericContainer<>::GenericList generics;

    next();

    if (is<TokenType::OP_LT>()) { generics = parseGenericParams(); }

    consume<TokenType::OP_EQ>("'='");
    auto type = parseType();

    auto privacy = Syntax::Statement::Privacy::fromInt(isPublic);
    auto node = Syntax::N<Syntax::Statement::TypeAlias>(name, type);

    node->setPrivacy(privacy);
    node->setDBGInfo(dbg);

    node->setGenerics(generics);

    return node;
}

} // namespace snowball::parser
