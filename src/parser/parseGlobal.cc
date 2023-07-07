
#include "../common.h"
#include "../token.h"
#include "./Parser.h"

#include <assert.h>

using namespace snowball::Syntax::Expression;

namespace snowball::parser {

Parser::NodeVec Parser::parseGlobal(TokenType terminator) {
    bool keep_parsing = true;
    std::vector<Syntax::Node*> global;

    while (keep_parsing) {
        if (terminator == m_current.type) {
            keep_parsing = false;
        } else {
            switch (m_current.type) {
                case TokenType::_EOF:
                    // Unexpected because it shoud've been caught by the conditional above
                    createError<SYNTAX_ERROR>("unexpected end of file");
                case TokenType::SYM_SEMI_COLLON: next(); break;

                case TokenType::KWORD_PUBLIC:
                case TokenType::KWORD_PRIVATE: {
                    auto pk = peek();
                    if (!is<TokenType::KWORD_FUNC>(pk) && !is<TokenType::KWORD_VAR>(pk) &&
                        !is<TokenType::KWORD_TYPEDEF>(pk) && !is<TokenType::KWORD_NAMESPACE>(pk) &&
                        !is<TokenType::KWORD_STRUCT>(pk) && !is<TokenType::KWORD_STATIC>(pk) &&
                        !is<TokenType::KWORD_CLASS>(pk) && !is<TokenType::KWORD_EXTERN>(pk)) {
                        createError<SYNTAX_ERROR>(
                                "expected keyword \"fn\", \"static\", \"namespace\", \"class\", "
                                "\"let\" "
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

                case TokenType::KWORD_NAMESPACE: {
                    global.push_back(parseNamespace());
                    break;
                }

                case TokenType::KWORD_STRUCT: {
                    global.push_back(parseStructure());
                    break;
                }

                case TokenType::KWORD_VAR: {
                    global.push_back(parseVariable());
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

                case TokenType::KWORD_TYPEDEF: {
                    global.push_back(parseTypeAlias());
                    break;
                }

                default:
                    createError<SYNTAX_ERROR>(FMT("Unexpected token found: %s%s%s",
                                                  BLU,
                                                  m_current.to_string().c_str(),
                                                  RESET));
            }
        }

        if (keep_parsing && !is<TokenType::_EOF>(m_current)) next();
    }

    return global;
}

} // namespace snowball::parser
