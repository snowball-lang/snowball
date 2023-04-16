
#include "./Parser.h"

#include "../token.h"

namespace snowball {
namespace parser {

Parser::Parser(std::vector<Token> p_tokens, SourceInfo *p_source_info)
    : m_tokens(p_tokens), m_source_info(p_source_info) {
    m_current = m_tokens.at(m_tok_index);
}

std::vector<Syntax::Node *> Parser::parse() {
    bool keep_parsing = true;
    std::vector<Syntax::Node *> global;

    while (keep_parsing) {
        switch (m_current.type) {
            case TokenType::_EOF: {
                keep_parsing = false;
                break;
            }

            case TokenType::KWORD_PUBLIC:
            case TokenType::KWORD_PRIVATE: {
                auto pk = peek();
                if (!is<TokenType::KWORD_FUNC>(pk) &&
                    !is<TokenType::KWORD_MOD>(pk) &&
                    !is<TokenType::KWORD_VAR>(pk) &&
                    !is<TokenType::KWORD_STATIC>(pk) &&
                    !is<TokenType::KWORD_CLASS>(pk) &&
                    !is<TokenType::KWORD_EXTERN>(pk)) {
                    createError<SYNTAX_ERROR>(
                        "expected keyword \"fn\", \"static\", \"class\", "
                        "\"mod\", \"let\" "
                        "or "
                        "\"extern\" after pub/priv declaration");
                }

                break;
            }

            case TokenType::KWORD_EXTERN: {
                auto pk = peek();
                if (!is<TokenType::KWORD_FUNC>(pk)) {
                    createError<SYNTAX_ERROR>("expected 'fn' keyword after an "
                                              "extern function declaration");
                }

                break;
            }

            case TokenType::KWORD_STATIC: {
                auto pk = peek();
                if (!is<TokenType::KWORD_FUNC>(pk)) {
                    createError<SYNTAX_ERROR>("expected 'fn' keyword after a "
                                              "static function declaration");
                }

                break;
            }

            case TokenType::KWORD_FUNC: {
                global.push_back(parseFunction());
                break;
            }

            case TokenType::KWORD_CLASS: {
                global.push_back(parseClass());
                break;
            }

            case TokenType::KWORD_IMPORT: {
                global.push_back(parseImportStatement());
                break;
            }

            default:
                createError<SYNTAX_ERROR>(
                    FMT("Unexpected token found: %s%s%s", BLU,
                        m_current.to_string().c_str(), RESET));
        }

        if (keep_parsing) next();
    }

    return global;
}

Token Parser::next(int p_offset) {
    try {
        m_tok_index += (p_offset + 1);
        m_current = m_tokens.at(m_tok_index);

        return m_current;
    } catch (std::out_of_range& _) {
        createError<BUG>("Index error");
    }

    return {};
}

Token Parser::prev(int p_offset) {
    try {
        m_tok_index -= (p_offset + 1);
        m_current = m_tokens.at(m_tok_index);

        return m_current;
    } catch (std::out_of_range& _) {
        createError<BUG>("Index error");
    }

    return {};
}

Token Parser::peek(int p_offset, bool p_safe) {
    Token tmp = {TokenType::_EOF};
    if ((m_tok_index + 1) + p_offset < 0 ||
        (m_tok_index + 1) + p_offset >= (int)m_tokens.size()) {
        if (p_safe)
            return tmp;
        else
            createError<BUG>("Parser::peek() index out of bounds");
    }

    return m_tokens.at((m_tok_index + 1) + p_offset);
}
} // namespace parser
} // namespace snowball
