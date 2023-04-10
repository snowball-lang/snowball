

#include "../common.h"
#include "../token.h"
#include "./Parser.h"

#include <assert.h>

using namespace snowball::Syntax::Expression;

namespace snowball::parser {

FunctionCall*
Parser::parseFunctionCall(Syntax::Expression::Base* callee) {
    assert(callee != nullptr);
    assert(is<TokenType::BRACKET_LPARENT>());

    std::vector<Base*> arguments;
    while (true) {
        auto pk = peek();

        if (is<TokenType::BRACKET_RPARENT>(pk)) {
            break;
        }

        auto val = parseExpr(false);
        arguments.push_back(val);

        pk = peek();
        if (is<TokenType::SYM_COMMA>(pk) ||
            is<TokenType::BRACKET_RPARENT>(pk)) {
            if (is<TokenType::SYM_COMMA>(pk)) next();
            continue;
        } else {
            next();
            createError<SYNTAX_ERROR>(
                "Expected a ',' or a ')' but found '%s' instead",
                m_current.to_string().c_str());
        }
    }

    next(); // Consume "("
    auto call = Syntax::N<FunctionCall>(callee, arguments);

    // TODO: dbg info should start at the "(", maybe?
    call->setDBGInfo(callee->getDBGInfo());
    call->setSourceInfo(m_source_info);

    return call;
}

} // namespace snowball::parser
