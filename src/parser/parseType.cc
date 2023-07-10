

#include "../common.h"
#include "../token.h"
#include "./Parser.h"

#include <assert.h>

using namespace snowball::Syntax::Expression;

namespace snowball::parser {

TypeRef* Parser::parseType() {
    throwIfNotType();
    assert(is<TokenType::IDENTIFIER>() || is<TokenType::KWORD_DECLTYPE>());
    auto pos = m_current.get_pos();
    if (is<TokenType::KWORD_DECLTYPE>()) {
        auto w = m_current.get_width();
        next();
        assert_tok<TokenType::BRACKET_LPARENT>("'('");
        auto expr = parseExpr(false);
        next();
        consume<TokenType::BRACKET_RPARENT>("')'");
        auto dbg = new DBGSourceInfo(m_source_info, pos, w);
        return Syntax::N<DeclType>(expr, dbg);
    }

    auto ident = parseIdentifier(true);
    Base* ast = ident;
    auto name = ident->getIdentifier();
    auto id = ident->getIdentifier();
    auto g = utils::cast<GenericIdentifier>(ast);
    auto generics = (g != nullptr) ? g->getGenerics() : std::vector<TypeRef*>{};
    next();
    while (is<TokenType::SYM_COLCOL>()) {
        next();
        auto i = parseIdentifier(true);
        auto base = ast;
        name += "::" + i->getIdentifier();
        id += "." + i->getIdentifier();
        ast = Syntax::N<Index>(ast, i, true);
        ast->setDBGInfo(i->getDBGInfo());
        auto g = utils::cast<GenericIdentifier>(i);
        generics = (g != nullptr) ? g->getGenerics() : std::vector<TypeRef*>{};
        next();
    }
    auto dbg = new DBGSourceInfo(m_source_info, pos, m_current.get_pos().second - pos.second);
    auto t = Syntax::TR(ast, name, dbg, id);
    t->setGenerics(generics);
    while (is<TokenType::OP_BIT_AND>()) {
        next();
        auto base = t;

        t = Syntax::N<ReferenceType>(base, dbg);
    }
    return t;
}

} // namespace snowball::parser