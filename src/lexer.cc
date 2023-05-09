
#include "lexer.h"

#include "errors.h"
#include "token.h"
#include "utils/utils.h"

#include <codecvt>
#include <iostream>
#include <locale>
#include <string>
#include <vector>

#define GET_CHAR(m_off)                                                        \
    (((size_t)char_ptr + m_off >= code.size())                                 \
         ? '\0'                                                                \
         : code.at((size_t)char_ptr + m_off))
#define EAT_CHAR(m_num)                                                        \
    {                                                                          \
        char_ptr += m_num;                                                     \
        cur_col += m_num;                                                      \
    }
#define EAT_LINE()                                                             \
    {                                                                          \
        char_ptr++;                                                            \
        cur_col = 1;                                                           \
        cur_line++;                                                            \
    }

#define IS_NUM(c) (('0' <= c && c <= '9'))
#define IS_HEX_CHAR(c)                                                         \
    (IS_NUM(c) || ('a' <= c && c <= 'f') || ('A' <= c && c <= 'F'))
#define IS_TEXT(c)                                                             \
    ((c == '_') || ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z'))

namespace snowball {
Lexer::Lexer(SourceInfo *p_source_info)
    : code(p_source_info->getSource()), _source_info(p_source_info) {}

void Lexer::tokenize() {

    if ((int)code.size() == 0) return;

    // Iterate every character of the source code
    // and tokenize that char. Tokenizing it will
    // mean that respective Token for the current
    // char will also be added to the Token array
    while (char_ptr < (int)code.size()) {
        switch (GET_CHAR(0)) {
            case 0:
                handle_eof();
                break;

            // Space, new lines and tabs
            case ' ':
            case '\t':
                EAT_CHAR(1);
                break;

            case '\n':
                EAT_LINE();
                break;

            case '/': {
                if (GET_CHAR(1) == '/') { // comment

                    // Skip characters until we encounter _EOF or NEW_LINE
                    while (GET_CHAR(0) != '\n' && GET_CHAR(0) != 0) {
                        EAT_CHAR(1);
                    }

                    if (GET_CHAR(0) == '\n') {
                        EAT_LINE();
                    } else if (GET_CHAR(0) == 0) {
                        handle_eof();
                    }
                } else if (GET_CHAR(1) == '*') { // multi line comment

                    EAT_CHAR(2);
                    while (true) {
                        if (GET_CHAR(0) == '*' && GET_CHAR(1) == '/') {
                            EAT_CHAR(2);
                            break;
                        } else if (GET_CHAR(0) == 0) {
                            lexer_error(Error::UNEXPECTED_EOF,
                                        "Found an unexpected EOF while parsing "
                                        "a comment",
                                        1);
                        } else if (GET_CHAR(0) == '\n') {
                            EAT_LINE();
                        } else {
                            EAT_CHAR(1);
                        }
                    }
                } else {
                    if (GET_CHAR(1) == '=')
                        consume(TokenType::OP_DIVEQ, 2);
                    else
                        consume(TokenType::OP_DIV);
                }
                break;
            }

            // symbols
            case ':': {
                if (GET_CHAR(1) == ':')
                    consume(TokenType::SYM_COLCOL, 2);
                else
                    consume(TokenType::SYM_COLLON);
                break;
            }
            case ',':
                consume(TokenType::SYM_COMMA);
                break;
            case ';':
                consume(TokenType::SYM_SEMI_COLLON);
                break;
            case '#':
                consume(TokenType::SYM_HASH);
                break;
            case '$':
                consume(TokenType::SYM_DOLLAR);
                break;
            case '?':
                consume(TokenType::SYM_QUESTION);
                break;
            case '@':
                consume(TokenType::SYM_AT);
                break;
            // brackets
            case '(':
                consume(TokenType::BRACKET_LPARENT);
                break;
            case ')':
                consume(TokenType::BRACKET_RPARENT);
                break;
            case '{':
                consume(TokenType::BRACKET_LCURLY);
                break;
            case '}':
                consume(TokenType::BRACKET_RCURLY);
                break;
            case '[':
                consume(TokenType::BRACKET_LSQUARED);
                break;
            case ']':
                consume(TokenType::BRACKET_RSQUARED);
                break;

            // op
            case '=': {
                if (GET_CHAR(1) == '=')
                    consume(TokenType::OP_EQEQ, 2);
                else if (GET_CHAR(1) == '>')
                    consume(TokenType::OP_ARROW, 2);
                else
                    consume(TokenType::OP_EQ);
                break;
            }
            case '+': {
                if (GET_CHAR(1) == '=')
                    consume(TokenType::OP_PLUSEQ, 2);
                else
                    consume(TokenType::OP_PLUS);
                break;
            }
            case '-': {
                if (GET_CHAR(1) == '=')
                    consume(TokenType::OP_MINUSEQ, 2);
                else
                    consume(TokenType::OP_MINUS);
                break;
            }
            case '*': {
                if (GET_CHAR(1) == '=')
                    consume(TokenType::OP_MULEQ, 2);
                else
                    consume(TokenType::OP_MUL);
                break;
            }
            case '\\':
                lexer_error(Error::SYNTAX_ERROR, "invalid character '\\'.", 1);
                break;
            case '%': {
                if (GET_CHAR(1) == '=')
                    consume(TokenType::OP_MOD_EQ, 2);
                else
                    consume(TokenType::OP_MOD);
                break;
            }
            case '<': {
                if (GET_CHAR(1) == '=')
                    consume(TokenType::OP_LTEQ, 2);
                else if (GET_CHAR(1) == '<') {
                    if (GET_CHAR(2) == '=')
                        consume(TokenType::OP_BIT_LSHIFT_EQ, 3);
                    else
                        consume(TokenType::OP_BIT_LSHIFT, 2);
                } else
                    consume(TokenType::OP_LT);
                break;
            }
            case '>': {
                if (GET_CHAR(1) == '=')
                    consume(TokenType::OP_GTEQ, 2);
                else if (GET_CHAR(1) == '>') {
                    if (GET_CHAR(2) == '=')
                        consume(TokenType::OP_BIT_RSHIFT_EQ, 3);
                    else
                    // TODO: (generics cant handle <type<hello<adios>>)
                    // consume(TokenType::OP_BIT_RSHIFT, 2);
                    //                                              ^^
                    // actually parse ">>" at parser when we encounter an
                    // operator
                    {
                        consume(TokenType::OP_GT);
                        consume(TokenType::OP_GT);
                    }
                } else
                    consume(TokenType::OP_GT);
                break;
            }
            case '!': {
                if (GET_CHAR(1) == '=')
                    consume(TokenType::OP_NOTEQ, 2);
                else
                    consume(TokenType::OP_NOT);
                break;
            }
            case '~':
                consume(TokenType::OP_BIT_NOT);
                break;
            case '|': {
                if (GET_CHAR(1) == '=')
                    consume(TokenType::OP_BIT_OR_EQ, 2);
                else if (GET_CHAR(1) == '|')
                    consume(TokenType::OP_OR, 2);
                else
                    consume(TokenType::OP_BIT_OR);
                break;
            }
            case '&': {
                if (GET_CHAR(1) == '=')
                    consume(TokenType::OP_BIT_AND_EQ, 2);
                else if (GET_CHAR(1) == '&')
                    consume(TokenType::OP_AND, 2);
                else
                    consume(TokenType::OP_BIT_AND);
                break;
            }
            case '^': {
                if (GET_CHAR(1) == '=')
                    consume(TokenType::OP_BIT_XOR_EQ, 2);
                else
                    consume(TokenType::OP_BIT_XOR);
                break;
            }

            case '\'': {
                EAT_CHAR(1);
                std::string str;
                while (GET_CHAR(0) != '\'') {
                    if (GET_CHAR(0) == '\\') {
                        char c = GET_CHAR(1);

                        switch (c) {
                            case 0:
                                lexer_error(Error::UNEXPECTED_EOF,
                                            "unexpected EOF while lexing a "
                                            "string scape.");
                                break;
                            case '\\':
                                str += '\\';
                                EAT_CHAR(2);
                                break;
                            case '\'':
                                str += '\'';
                                EAT_CHAR(2);
                                break;
                            case 't':
                                str += '\t';
                                EAT_CHAR(2);
                                break;
                            case 'n':
                                str += '\n';
                                EAT_CHAR(2);
                                break;
                            case '"':
                                str += '"';
                                EAT_CHAR(2);
                                break;
                            case 'r':
                                str += '\r';
                                EAT_CHAR(2);
                                break;
                            case '\n':
                                EAT_CHAR(1);
                                EAT_LINE();
                                break;
                            default:
                                lexer_error(Error::SYNTAX_ERROR,
                                            "invalid escape character", 2);
                        }
                    } else if (GET_CHAR(0) == 0) {
                        lexer_error(Error::UNEXPECTED_EOF,
                                    "unexpected EOF while lexing character.");
                        break;
                    } else {
                        str += GET_CHAR(0);
                        if (GET_CHAR(0) == '\n') {
                            lexer_error(Error::SYNTAX_ERROR,
                                        "Characters can't contain new lines!");
                        } else {
                            EAT_CHAR(1);
                        }
                    }
                }
                EAT_CHAR(1);

                if (str.size() != 1) {
                    lexer_error(
                        Error::SYNTAX_ERROR,
                        "Character values can only have a length of 1!");
                }

                Token tk;
                tk.type  = TokenType::VALUE_CHAR;
                tk.value = str; // method name may be builtin func
                tk.col   = cur_col - ((int)str.size() + (2 /* speech marks */));
                tk.line  = cur_line;
                tokens.emplace_back(tk);

                break;
            }

            case '"': {
                EAT_CHAR(1);
                std::string str;
                while (GET_CHAR(0) != '"') {
                    if (GET_CHAR(0) == '\\') {
                        char c = GET_CHAR(1);

                        switch (c) {
                            case 0:
                                lexer_error(Error::UNEXPECTED_EOF,
                                            "unexpected EOF while lexing a "
                                            "string scape.");
                                break;
                            case '\\':
                                str += '\\';
                                EAT_CHAR(2);
                                break;
                            case '\'':
                                str += '\'';
                                EAT_CHAR(2);
                                break;
                            case 't':
                                str += '\t';
                                EAT_CHAR(2);
                                break;
                            case 'n':
                                str += '\n';
                                EAT_CHAR(2);
                                break;
                            case '"':
                                str += '"';
                                EAT_CHAR(2);
                                break;
                            case 'r':
                                str += '\r';
                                EAT_CHAR(2);
                                break;
                            case '\n':
                                EAT_CHAR(1);
                                EAT_LINE();
                                break;
                            default:
                                lexer_error(Error::SYNTAX_ERROR,
                                            "invalid escape character", 2);
                        }
                    } else if (GET_CHAR(0) == 0) {
                        lexer_error(Error::UNEXPECTED_EOF,
                                    "unexpected EOF while lexing string.");
                        break;
                    } else {
                        str += GET_CHAR(0);
                        if (GET_CHAR(0) == '\n') {
                            EAT_LINE();
                        } else {
                            EAT_CHAR(1);
                        }
                    }
                }
                EAT_CHAR(1);

                Token tk;
                tk.type  = TokenType::VALUE_STRING;
                tk.value = str; // method name may be builtin func
                tk.col   = cur_col - ((int)str.size() + (2 /* speech marks */));
                tk.line  = cur_line;
                tokens.emplace_back(tk);

                break;
            }

            default:
                // TODO: 1.2e3 => is a valid float number

                // float value begins with '.'
                if (GET_CHAR(0) == '.' && IS_NUM(GET_CHAR(1))) {
                    std::string float_str(1, '.');
                    EAT_CHAR(1);
                    while (IS_NUM(GET_CHAR(0))) {
                        float_str += GET_CHAR(0);
                        EAT_CHAR(1);
                    }

                    double float_val = std::stod(float_str);
                    Token tk;
                    tk.type  = TokenType::VALUE_FLOAT;
                    tk.line  = cur_line;
                    tk.col   = cur_col - float_str.length();
                    tk.value = float_val;
                    tokens.emplace_back(tk);
                    break;
                }

                // integer/float value
                if (IS_NUM(GET_CHAR(0))) {
                    std::string num(1, GET_CHAR(0));

                    enum _ReadMode { INT, FLOAT, BIN, HEX };
                    _ReadMode mode = INT;
                    if (GET_CHAR(0) == '0') {
                        if (GET_CHAR(1) == 'b' || GET_CHAR(1) == 'B')
                            mode = BIN;
                        if (GET_CHAR(1) == 'x' || GET_CHAR(1) == 'X')
                            mode = HEX;
                    }
                    EAT_CHAR(1);
                    switch (mode) {
                        case INT: {
                            while (IS_NUM(GET_CHAR(0)) || GET_CHAR(0) == '.') {
                                if (GET_CHAR(0) == '.' && mode == FLOAT)
                                    lexer_error(Error::SYNTAX_ERROR,
                                                "invalid numeric value.", 1);
                                if (GET_CHAR(0) == '.') mode = FLOAT;
                                num += GET_CHAR(0);
                                EAT_CHAR(1);
                            }
                        } break;
                        case BIN: {
                            num += GET_CHAR(0);
                            EAT_CHAR(1); // eat 'b';
                            while (GET_CHAR(0) == '0' || GET_CHAR(0) == '1') {
                                num += GET_CHAR(0);
                                EAT_CHAR(1);
                            }
                        } break;
                        case HEX: {
                            num += GET_CHAR(0);
                            EAT_CHAR(1); // eat 'x';
                            while (IS_HEX_CHAR(GET_CHAR(0))) {
                                num += GET_CHAR(0);
                                EAT_CHAR(1);
                            }
                        } break;

                        default:
                            lexer_error(
                                Error::BUG,
                                FMT("Unreachable number mode \"%i\"", mode),
                                num.size());
                    }

                    // "1." parsed as 1.0 which should be error.
                    if (num[num.size() - 1] == '.')
                        lexer_error(Error::SYNTAX_ERROR,
                                    "invalid numeric value.");

                    Token tk;
                    tk.line  = cur_line;
                    tk.col   = cur_col - num.length();
                    tk.value = num;
                    if (mode == FLOAT) {
                        tk.type = TokenType::VALUE_FLOAT;
                    } else {
                        tk.type = TokenType::VALUE_NUMBER;
                    }

                    tokens.emplace_back(tk);
                    break;
                }
                // identifier
                if (IS_TEXT(GET_CHAR(0))) {
                    std::string identifier(1, GET_CHAR(0));
                    EAT_CHAR(1);
                    while (IS_TEXT(GET_CHAR(0)) || IS_NUM(GET_CHAR(0))) {
                        identifier += GET_CHAR(0);
                        EAT_CHAR(1);
                    }

                    Token tk;
                    tk.value = identifier; // method name may be builtin func
                    tk.col   = cur_col - (int)identifier.size();
                    tk.line  = cur_line;

                    if (identifier == _SNOWBALL_KEYWORD__NOT) {
                        tk.type = TokenType::OP_NOT;
                    } else if (identifier == _SNOWBALL_KEYWORD__NEW) {
                        tk.type = TokenType::KWORD_NEW;
                    }

                    else if (identifier == _SNOWBALL_KEYWORD__IF) {
                        tk.type = TokenType::KWORD_IF;
                    } else if (identifier == _SNOWBALL_KEYWORD__VARIABLE) {
                        tk.type = TokenType::KWORD_VAR;
                    } else if (identifier == _SNOWBALL_KEYWORD__FOR) {
                        tk.type = TokenType::KWORD_FOR;
                    } else if (identifier == _SNOWBALL_KEYWORD__ENUM) {
                        tk.type = TokenType::KWORD_ENUM;
                    } else if (identifier == _SNOWBALL_KEYWORD__CASE) {
                        tk.type = TokenType::KWORD_CASE;
                    } else if (identifier == _SNOWBALL_KEYWORD__DECLTYPE) {
                        tk.type = TokenType::KWORD_DECLTYPE;
                    } else if (identifier == _SNOWBALL_KEYWORD__FUNCTION) {
                        tk.type = TokenType::KWORD_FUNC;
                    } else if (identifier == _SNOWBALL_KEYWORD__OPERATOR) {
                        tk.type = TokenType::KWORD_OPERATOR;
                    } else if (identifier == _SNOWBALL_KEYWORD__ELSE) {
                        tk.type = TokenType::KWORD_ELSE;
                    } else if (identifier == _SNOWBALL_KEYWORD__CLASS) {
                        tk.type = TokenType::KWORD_CLASS;
                    } else if (identifier == _SNOWBALL_KEYWORD__AS) {
                        tk.type = TokenType::KWORD_AS;
                    } else if (identifier == _SNOWBALL_KEYWORD__CONSTANT) {
                        tk.type = TokenType::KWORD_CONST;
                    } else if (identifier == _SNOWBALL_KEYWORD__WHILE) {
                        tk.type = TokenType::KWORD_WHILE;
                    } else if (identifier == _SNOWBALL_KEYWORD__BREAK) {
                        tk.type = TokenType::KWORD_BREAK;
                    } else if (identifier == _SNOWBALL_KEYWORD__EXTERN) {
                        tk.type = TokenType::KWORD_EXTERN;
                    } else if (identifier == _SNOWBALL_KEYWORD__SUPER) {
                        tk.type = TokenType::KWORD_SUPER;
                    } else if (identifier == _SNOWBALL_KEYWORD__SWITCH) {
                        tk.type = TokenType::KWORD_SWITCH;
                    } else if (identifier == _SNOWBALL_KEYWORD__STATIC) {
                        tk.type = TokenType::KWORD_STATIC;
                    } else if (identifier == _SNOWBALL_KEYWORD__IMPORT) {
                        tk.type = TokenType::KWORD_IMPORT;
                    } else if (identifier == _SNOWBALL_KEYWORD__DO) {
                        tk.type = TokenType::KWORD_DO;
                    } else if (identifier == _SNOWBALL_KEYWORD__PRIVATE) {
                        tk.type = TokenType::KWORD_PRIVATE;
                    } else if (identifier == _SNOWBALL_KEYWORD__PUBLIC) {
                        tk.type = TokenType::KWORD_PUBLIC;
                    } else if (identifier == _SNOWBALL_KEYWORD__VIRTUAL) {
                        tk.type = TokenType::KWORD_VIRTUAL;
                    } else if (identifier == _SNOWBALL_KEYWORD__RETURN) {
                        tk.type = TokenType::KWORD_RETURN;
                    } else if (identifier == _SNOWBALL_KEYWORD__DEFAULT) {
                        tk.type = TokenType::KWORD_DEFAULT;
                    } else if (identifier == _SNOWBALL_KEYWORD__CONTINUE) {
                        tk.type = TokenType::KWORD_CONTINUE;
                    } else if (identifier == _SNOWBALL_KEYWORD__TRY) {
                        tk.type = TokenType::KWORD_TRY;
                    } else if (identifier == _SNOWBALL_KEYWORD__CATCH) {
                        tk.type = TokenType::KWORD_CATCH;
                    }

                    else if (identifier == _SNOWBALL_KEYWORD__TRUE ||
                             identifier == _SNOWBALL_KEYWORD__FALSE) {
                        tk.type = TokenType::VALUE_BOOL;
                    } else {
                        tk.type = TokenType::IDENTIFIER;
                    }

                    tokens.emplace_back(tk);
                    break;
                }

                if (GET_CHAR(0) == '.') {
                    consume(TokenType::SYM_DOT);
                    break;
                }

                auto c = utils::getUTF8FromIndex(code, char_ptr);
                if (c == "🐒") {
                    lexer_error(Error::SYNTAX_ERROR, "Unexpected MONKE found!",
                                1, "🐒🐒🐒🐒🐒🐒");
                } else {
                    lexer_error(
                        Error::SYNTAX_ERROR,
                        FMT("Unexpected character found '%s' while lexing.",
                            c.c_str()),
                        1);
                }
        }
    }

    // For some reason, sometimes the tokenizer
    // does not detect the end of the source code.
    // that is why we add a Token with _EOF type to
    // the Token array (for later use in the parser)
    if (tokens.size() == 0 || ((*tokens.end()).type != TokenType::_EOF)) {
        // add "false" as a param for "p_consume"
        // so that the lexer does not "consume"
        handle_eof(false);
    }

#if _SNOWBALL_LEXER_DEBUG

    PRINT_LINE("Lexer's Tokens:")
    PRINT_LINE(LINE_SEPARATOR)

    int index = 0;
    for (Token tk : tokens) {
        DEBUG_LEXER("[%i]: %s (type %i)", index, tk.to_string().c_str(),
                    tk.type)
        index++;
    }

    PRINT_LINE(LINE_SEPARATOR)
#endif
}

void Lexer::handle_eof(bool p_consume) {
    // Declare a new Token
    Token tk;

    // Fill al fields for the token
    // as an EOF type.
    tk.type = TokenType::_EOF;
    tk.line = cur_line;
    tk.col  = cur_col;

    // Add token to the list of tokens
    tokens.emplace_back(tk);

    if (p_consume) {
        EAT_CHAR(1);
    }
}

void Lexer::consume(TokenType p_tk, int p_eat_size) {
    Token tk;
    tk.type = p_tk;
    tk.line = cur_line;
    tk.col  = cur_col;
    tokens.emplace_back(tk);
    EAT_CHAR(p_eat_size);
}

void Lexer::lexer_error(Error m_error, std::string m_msg, int char_length,
                        const std::string& info) {
    DBGSourceInfo *dbg_info =
        new DBGSourceInfo((SourceInfo *)_source_info,
                          std::pair<int, int>(cur_line, cur_col), char_length);
    throw LexerError(m_error, std::string(m_msg), dbg_info, info);
}
} // namespace snowball
