
#include "../ast/types/PrimitiveTypes.h"
#include "../common.h"
#include "../token.h"
#include "./Parser.h"

#include <assert.h>

using namespace snowball::Syntax::Statement;
namespace snowball::parser {

Syntax::Statement::Return*
Parser::parseReturn() {
    assert(is<TokenType::KWORD_RETURN>());

    auto info = DBGSourceInfo::fromToken(m_source_info, m_current);

    auto expr = parseExpr(false);
    auto node = Syntax::N<Return>(expr);
    node->setDBGInfo(info);

    return node;
}
} // namespace snowball::parser
