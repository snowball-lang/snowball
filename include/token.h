
#include <string>
#include <vector>
#include <utility>

#ifndef __SNOWBALL_TOKEN_H_
#define __SNOWBALL_TOKEN_H_

namespace snowball {
    enum class TokenType {
        /*
        | Indentifiers
        |---------------
        | An identifier is lexical token
        | (also called symbol, but not to
        | be confused with the symbol primitive
        | data type) that names the language's
        | entities.
        |
        | Some of the kinds of entities an identifier
        | might denote include variables, data types,
        | labels, subroutines, and modules.
        |
        | Snowball accepts the following identifiers:
        |    * a
        |    * _thisIsValid
        |    * Hello_World
        |    * foo123
        |    * BYE_BYE
        |
        | note: Boolean, Number, String, ... (BUILTIN_TYPES) cant be identifiers
        */
        IDENTIFIER,
        BUILTIN_TYPE,

        // Literal values
        VALUE_NUMBER,
        VALUE_FLOAT,
        VALUE_NULL,
        VALUE_BOOL,
        VALUE_STRING,

        /*
        | Symbols
        |-------------
        | This are the single
        | characters tokens
        */
        SYM_AT,            // Symbol: @
        SYM_DOT,           // Symbol: .
        SYM_HASH,          // Symbol: #
        SYM_COMMA,         // Symbol: ,
        SYM_COLLON,        // Symbol: :
        SYM_DOLLAR,        // Symbol: $
        SYM_QUESTION,      // Symbol: ?
        SYM_SEMI_COLLON,   // Symbol: ;

        // |- BRACKETS -|
        BRACKET_LCURLY,    // Symbol: {
        BRACKET_RCURLY,    // Symbol: }
        BRACKET_LPARENT,   // Symbol: (
        BRACKET_RPARENT,   // Symbol: )
        BRACKET_RSQUARED,  // Symbol: [
        BRACKET_LSQUARED,  // Symbol: ]

        /*
        | Mathematical symbols
        |----------------------
        | This tokens are used to
        | do mathematical operations
        | such as add and multiply
        |
        | note that it can also work
        | with other types such as
        | string concationation and
        | calling the overiding function
        | in a class.
        */
        // TODO: Exponential

        // Single characters
        OP_MUL,            // Symbol: *
        OP_MOD,            // Symbol: %
        OP_DIV,            // Symbol: /
        OP_PLUS,           // Symbol: +
        OP_MINUS,          // Symbol: -

        // Double characters
        OP_MULEQ,          // Symbol: *=
        OP_DIVEQ,          // Symbol: /=
        OP_MOD_EQ,         // Symbol: %=
        OP_PLUSEQ,         // Symbol: +=
        OP_MINUSEQ,        // Symbol: -=

        /*
        | Comparasion tokens
        |--------------------
        | `Comparasion tokens` are
        | tokens used to compare 2
        | values. It will return
        | true if the statement matches
        */

        // Single character tokens
        OP_GT,             // Symbol: >
        OP_LT,             // Symbol: <

        // Double character tokens
        OP_EQEQ,           // Symbol: ==
        OP_GTEQ,           // Symbol: >=
        OP_LTEQ,           // Symbol: <=
        OP_NOTEQ,          // Symbol: !=

        /*
        | Asignment tokens
        |------------------
        | This tokens are used
        | to set a value to a
        | variable.
        */

        // Single character tokens
        OP_EQ,             // Symbol: =
        OP_NOT,            // Symbol: !

        // Double character tokens
        OP_AND,            // Symbol: &&
        OP_OR,             // Symbol: ||

        // Bitwise operations
        OP_BIT_NOT,        // Symbol: ~
        OP_BIT_OR,         // Symbol: |
        OP_BIT_AND,        // Symbol: &
        OP_BIT_XOR,        // Symbol: ^

        OP_BIT_OR_EQ,      // Symbol: |=
        OP_BIT_RSHIFT,     // Symbol: >>
        OP_BIT_LSHIFT,     // Symbol: <<
        OP_BIT_AND_EQ,     // Symbol: &=
        OP_BIT_XOR_EQ,     // Symbol: ^=
        OP_BIT_RSHIFT_EQ,  // Symbol: >>=
        OP_BIT_LSHIFT_EQ,  // Symbol: <<=

        /*
        | Keywords
        |-----------------------
        | Keywords are predefined,
        | reserved words used that have
        | special meanings to the
        | interpreter.
        */
        KWORD_IF,          // Symbol: if
        KWORD_OR,          // Symbol: or
        KWORD_VAR,         // Symbol: var
        KWORD_NOT,         // Symbol: not
        KWORD_FOR,         // Symbol: for
        KWORD_AND,         // Symbol: and
        KWORD_NULL,        // Symbol: null
        KWORD_ENUM,        // Symbol: enum
        KWORD_FUNC,        // Symbol: fn
        KWORD_TRUE,        // Symbol: true
        KWORD_ELSE,        // Symbol: else
        KWORD_CASE,        // Symbol: case
        KWORD_THIS,        // Symbol: this
        KWORD_FALSE,       // Symbol: false
        KWORD_BREAK,       // Symbol: break
        KWORD_CONST,       // Symbol: const
        KWORD_SUPER,       // Symbol: super
        KWORD_WHILE,       // Symbol: while
        KWORD_CLASS,       // Symbol: class
        KWORD_IMPORT,      // Symbol: import
        KWORD_SWITCH,      // Symbol: switch
        KWORD_STATIC,      // Symbol: static
        KWORD_RETURN,      // Symbol: return
        KWORD_DEFAULT,     // Symbol: default
        KWORD_CONTINUE,    // Symbol: continue

        /*
        | Other
        |-----------
        | This are not specially tokens.
        */
        _EOF,              // End of file. This already exists in <stdio.h>
        UNKNOWN,           // Other
        _TK_MAX_,          // Max token
    };

    struct Token {
        TokenType type = TokenType::UNKNOWN;
        int line = 0, col = 0;

        std::string value;

        Token() {}
        Token(TokenType p_type) { type = p_type; }


        std::string to_string() const {
            switch (type) {

                // Symbols
                case TokenType::SYM_AT:             return "@";
                case TokenType::SYM_DOT:            return ".";
                case TokenType::SYM_HASH:           return "#";
                case TokenType::SYM_COMMA:          return ",";
                case TokenType::SYM_COLLON:         return ":";
                case TokenType::SYM_DOLLAR:         return "$";
                case TokenType::SYM_QUESTION:       return "?";
                case TokenType::SYM_SEMI_COLLON:    return ";";

                // Brackets
                case TokenType::BRACKET_LCURLY:     return "{";
                case TokenType::BRACKET_RCURLY:     return "}";
                case TokenType::BRACKET_LPARENT:    return "(";
                case TokenType::BRACKET_RPARENT:    return ")";
                case TokenType::BRACKET_LSQUARED:   return "[";
                case TokenType::BRACKET_RSQUARED:   return "]";

                // Equiality
                case TokenType::OP_GT:              return ">";
                case TokenType::OP_LT:              return "<";
                case TokenType::OP_GTEQ:            return ">=";
                case TokenType::OP_EQEQ:            return "==";
                case TokenType::OP_LTEQ:            return "<=";
                case TokenType::OP_NOTEQ:           return "!=";

                // Mathematical symbols
                case TokenType::OP_MOD:             return "%";
                case TokenType::OP_DIV:             return "/";
                case TokenType::OP_MUL:             return "*";
                case TokenType::OP_PLUS:            return "+";
                case TokenType::OP_MINUS:           return "-";
                case TokenType::OP_MULEQ:           return "*=";
                case TokenType::OP_DIVEQ:           return "/=";
                case TokenType::OP_PLUSEQ:          return "+=";
                case TokenType::OP_MOD_EQ:          return "%=";
                case TokenType::OP_MINUSEQ:         return "-=";

                // Asignment
                case TokenType::OP_EQ:              return "=";
                case TokenType::OP_OR:              return "||";
                case TokenType::OP_AND:             return "&&";
                case TokenType::OP_NOT:             return "!";

                // Bitwise operations
                case TokenType::OP_BIT_OR:          return "|";
                case TokenType::OP_BIT_NOT:         return "~";
                case TokenType::OP_BIT_AND:         return "&";
                case TokenType::OP_BIT_XOR:         return "^";
                case TokenType::OP_BIT_OR_EQ:       return "|=";
                case TokenType::OP_BIT_LSHIFT:      return "<<";
                case TokenType::OP_BIT_RSHIFT:      return ">>";
                case TokenType::OP_BIT_AND_EQ:      return "&=";
                case TokenType::OP_BIT_XOR_EQ:      return "^=";
                case TokenType::OP_BIT_LSHIFT_EQ:   return "<<=";
                case TokenType::OP_BIT_RSHIFT_EQ:   return ">>=";

                // Identifiers
                case TokenType::IDENTIFIER:         return value;

                // Keywods
                case TokenType::KWORD_IMPORT:       return "import";
                case TokenType::KWORD_CLASS:        return "class";
                case TokenType::KWORD_ENUM:         return "enum";
                case TokenType::KWORD_FUNC:         return "func";
                case TokenType::KWORD_VAR:          return "var";
                case TokenType::KWORD_CONST:        return "const";
                case TokenType::KWORD_NULL:         return "null";
                case TokenType::KWORD_TRUE:         return "true";
                case TokenType::KWORD_FALSE:        return "false";
                case TokenType::KWORD_IF:           return "if";
                case TokenType::KWORD_ELSE:         return "else";
                case TokenType::KWORD_WHILE:        return "while";
                case TokenType::KWORD_FOR:          return "for";
                case TokenType::KWORD_SWITCH:       return "switch";
                case TokenType::KWORD_CASE:         return "case";
                case TokenType::KWORD_DEFAULT:      return "default";
                case TokenType::KWORD_BREAK:        return "break";
                case TokenType::KWORD_CONTINUE:     return "continue";
                case TokenType::KWORD_STATIC:       return "static";
                case TokenType::KWORD_THIS:         return "this";
                case TokenType::KWORD_SUPER:        return "super";
                case TokenType::KWORD_RETURN:       return "return";
                case TokenType::KWORD_AND:          return "and";
                case TokenType::KWORD_OR:           return "or";
                case TokenType::KWORD_NOT:          return "not";

                // Literal values
                case TokenType::VALUE_NULL:         return "null";

                case TokenType::VALUE_NUMBER:
                case TokenType::VALUE_FLOAT:
                case TokenType::VALUE_BOOL:
                    return value;

                case TokenType::VALUE_STRING:
                    return std::string("\"") + value + "\"";

                // Other
                case TokenType::UNKNOWN: return "<unknown>";
                case TokenType::_EOF:    return "<eof>";
                case TokenType::_TK_MAX_: return "<_TK_MAX_>";

                default:
                    return "<BUG>";
            }

            // TODO: throw error: missed enum in switch case
        }

        std::pair<int, int> get_pos() const { return std::pair<int, int>(std::make_pair(line, col)); }
        uint32_t get_width() const { return (uint32_t)to_string().size(); }
    };
}

#endif // __SNOWBALL_TOKEN_H_
