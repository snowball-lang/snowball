
#include "../ast/types/PrimitiveTypes.h"
#include "../common.h"
#include "../token.h"
#include "./Parser.h"

#include <assert.h>

using namespace snowball::Syntax::Statement;
namespace snowball::parser {

Conditional *Parser::parseConditional() {
    assert(is<TokenType::KWORD_IF>());

    auto info = DBGSourceInfo::fromToken(m_source_info, m_current);
    auto expr = parseExpr(false);
    next();

    auto block = parseBlock();

    auto node = Syntax::N<Conditional>(expr, block);
    node->setDBGInfo(info);

    return node;
}
} // namespace snowball::parser
