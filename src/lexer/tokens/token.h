
#include "constants.h"
#include "utils/logger.h"

#include <string>
#include <utility>
#include <vector>

#ifndef __SNOWBALL_TOKEN_H_
#define __SNOWBALL_TOKEN_H_

namespace snowball {
enum class TokenType
{
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
    */
    IDENTIFIER,

    // Literal values
    VALUE_NUMBER,
    VALUE_FLOAT,
    VALUE_BOOL,
    VALUE_STRING,
    VALUE_CHAR,

    /*
    | Symbols
    |-------------
    | This are the single
    | characters tokens
    */
    SYM_AT,          // Symbol: @
    SYM_DOT,         // Symbol: .
    SYM_HASH,        // Symbol: #
    SYM_COMMA,       // Symbol: ,
    SYM_COLLON,      // Symbol: :
    SYM_COLCOL,      // Symbol: ::
    SYM_DOLLAR,      // Symbol: $
    SYM_QUESTION,    // Symbol: ?
    SYM_SEMI_COLLON, // Symbol: ;

    // |- BRACKETS -|
    BRACKET_LCURLY,   // Symbol: {
    BRACKET_RCURLY,   // Symbol: }
    BRACKET_LPARENT,  // Symbol: (
    BRACKET_RPARENT,  // Symbol: )
    BRACKET_RSQUARED, // Symbol: [
    BRACKET_LSQUARED, // Symbol: ]

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
    OP_MUL,   // Symbol: *
    OP_MOD,   // Symbol: %
    OP_DIV,   // Symbol: /
    OP_PLUS,  // Symbol: +
    OP_MINUS, // Symbol: -

    // Double characters
    OP_MULEQ,   // Symbol: *=
    OP_DIVEQ,   // Symbol: /=
    OP_MOD_EQ,  // Symbol: %=
    OP_PLUSEQ,  // Symbol: +=
    OP_MINUSEQ, // Symbol: -=

    /*
    | Comparasion tokens
    |--------------------
    | `Comparasion tokens` are
    | tokens used to compare 2
    | values. It will return
    | true if the statement matches
    */

    // Single character tokens
    OP_GT, // Symbol: >
    OP_LT, // Symbol: <

    // Double character tokens
    OP_ARROW, // Symbol: =>
    OP_EQEQ,  // Symbol: ==
    OP_GTEQ,  // Symbol: >=
    OP_LTEQ,  // Symbol: <=
    OP_NOTEQ, // Symbol: !=

    /*
    | Asignment tokens
    |------------------
    | This tokens are used
    | to set a value to a
    | variable.
    */

    // Single character tokens
    OP_EQ,  // Symbol: =
    OP_NOT, // Symbol: !

    // Double character tokens
    OP_AND, // Symbol: &&
    OP_OR,  // Symbol: ||

    // Bitwise operations
    OP_BIT_NOT, // Symbol: ~
    OP_BIT_OR,  // Symbol: |
    OP_BIT_AND, // Symbol: &
    OP_BIT_XOR, // Symbol: ^

    OP_BIT_OR_EQ,     // Symbol: |=
    OP_BIT_RSHIFT,    // Symbol: >>
    OP_BIT_LSHIFT,    // Symbol: <<
    OP_BIT_AND_EQ,    // Symbol: &=
    OP_BIT_XOR_EQ,    // Symbol: ^=
    OP_BIT_RSHIFT_EQ, // Symbol: >>=
    OP_BIT_LSHIFT_EQ, // Symbol: <<=

    /*
    | Keywords
    |-----------------------
    | Keywords are predefined,
    | reserved words used that have
    | special meanings to the
    | interpreter.
    */
    KWORD__START__POINT,  // All keywords must be grater than this
    KWORD_IF,             // Symbol: if
    KWORD_VAR,            // Symbol: let
    KWORD_NEW,            // Symbol: new
    KWORD_THROW,          // Symbol: raise
    KWORD_FOR,            // Symbol: for
    KWORD_ENUM,           // Symbol: enum
    KWORD_FUNC,           // Symbol: fn
    KWORD_OPERATOR,       // Symbol: operator
    KWORD_ELSE,           // Symbol: else
    KWORD_CASE,           // Symbol: case
    KWORD_BREAK,          // Symbol: break
    KWORD_CONST,          // Symbol: const
    KWORD_SUPER,          // Symbol: super
    KWORD_WHILE,          // Symbol: while
    KWORD_EXTERN,         // Synbol: extern
    KWORD_VIRTUAL,        // Synbol: virtual
    KWORD_CLASS,          // Symbol: class
    KWORD_AS,             // Symbol: as
    KWORD_IMPORT,         // Symbol: use
    KWORD_CONSTEXPR,      // Symbol: constexpr
    KWORD_TYPEDEF,        // Symbol: type
    KWORD_MUTABLE,        // Symbol: mut
    KWORD_DO,             // Symbol: do
    KWORD_NAMESPACE,      // Symbol: namespace
    KWORD_STRUCT,         // Symbol: struct
    KWORD_PUBLIC,         // Symbol: pub
    KWORD_SWITCH,         // Symbol: switch
    KWORD_STATIC,         // Symbol: static
    KWORD_RETURN,         // Symbol: return
    KWORD_PRIVATE,        // Symbol: priv
    KWORD_DECLTYPE,       // Symbol: decltype
    KWORD_DEFAULT,        // Symbol: default
    KWORD_TRY,            // Symbol: try
    KWORD_CATCH,          // Symbol: catch
    KWORD_CONTINUE,       // Symbol: continue
    KWORD__ENDING__POINT, // All keywords must be less than this

    /*
    | Other
    |-----------
    | This are not specially tokens.
    */
    _EOF,    // End of file. This already exists in <stdio.h>
    UNKNOWN, // Other
};

struct Token {
    TokenType type = TokenType::UNKNOWN;
    int line = 0, col = 0;

    std::string value;

    Token() { }
    Token(TokenType p_type) { type = p_type; }

    std::string to_string() const {
        switch (type) {
            // Symbols
            case TokenType::SYM_AT: return "@";
            case TokenType::SYM_DOT: return ".";
            case TokenType::SYM_HASH: return "#";
            case TokenType::SYM_COMMA: return ",";
            case TokenType::SYM_COLLON: return ":";
            case TokenType::SYM_DOLLAR: return "$";
            case TokenType::SYM_QUESTION: return "?";
            case TokenType::SYM_SEMI_COLLON: return ";";
            case TokenType::SYM_COLCOL: return "::";

            // Brackets
            case TokenType::BRACKET_LCURLY: return "{";
            case TokenType::BRACKET_RCURLY: return "}";
            case TokenType::BRACKET_LPARENT: return "(";
            case TokenType::BRACKET_RPARENT: return ")";
            case TokenType::BRACKET_LSQUARED: return "[";
            case TokenType::BRACKET_RSQUARED: return "]";

            // Equiality
            case TokenType::OP_GT: return ">";
            case TokenType::OP_LT: return "<";
            case TokenType::OP_GTEQ: return ">=";
            case TokenType::OP_EQEQ: return "==";
            case TokenType::OP_LTEQ: return "<=";
            case TokenType::OP_NOTEQ: return "!=";
            case TokenType::OP_ARROW: return "=>";

            // Mathematical symbols
            case TokenType::OP_MOD: return "%";
            case TokenType::OP_DIV: return "/";
            case TokenType::OP_MUL: return "*";
            case TokenType::OP_PLUS: return "+";
            case TokenType::OP_MINUS: return "-";
            case TokenType::OP_MULEQ: return "*=";
            case TokenType::OP_DIVEQ: return "/=";
            case TokenType::OP_PLUSEQ: return "+=";
            case TokenType::OP_MOD_EQ: return "%=";
            case TokenType::OP_MINUSEQ: return "-=";

            // Asignment
            case TokenType::OP_EQ: return "=";
            case TokenType::OP_OR: return "||";
            case TokenType::OP_AND: return "&&";
            case TokenType::OP_NOT: return "!";

            // Bitwise operations
            case TokenType::OP_BIT_OR: return "|";
            case TokenType::OP_BIT_NOT: return "~";
            case TokenType::OP_BIT_AND: return "&";
            case TokenType::OP_BIT_XOR: return "^";
            case TokenType::OP_BIT_OR_EQ: return "|=";
            case TokenType::OP_BIT_LSHIFT: return "<<";
            case TokenType::OP_BIT_RSHIFT: return ">>";
            case TokenType::OP_BIT_AND_EQ: return "&=";
            case TokenType::OP_BIT_XOR_EQ: return "^=";
            case TokenType::OP_BIT_LSHIFT_EQ: return "<<=";
            case TokenType::OP_BIT_RSHIFT_EQ: return ">>=";

            // Identifiers
            case TokenType::IDENTIFIER: return value;

            // Keywods
            case TokenType::KWORD_PUBLIC: return _SNOWBALL_KEYWORD__PUBLIC;
            case TokenType::KWORD_VIRTUAL: return _SNOWBALL_KEYWORD__VIRTUAL;
            case TokenType::KWORD_PRIVATE: return _SNOWBALL_KEYWORD__PRIVATE;
            case TokenType::KWORD_IMPORT: return _SNOWBALL_KEYWORD__IMPORT;
            case TokenType::KWORD_CONSTEXPR: return _SNOWBALL_KEYWORD__CONSTEXPR;
            case TokenType::KWORD_NAMESPACE: return _SNOWBALL_KEYWORD__NAMESPACE;
            case TokenType::KWORD_STRUCT: return _SNOWBALL_KEYWORD__STRUCT;
            case TokenType::KWORD_TYPEDEF: return _SNOWBALL_KEYWORD__TYPEDEF;
            case TokenType::KWORD_MUTABLE: return _SNOWBALL_KEYWORD__MUTABLE;
            case TokenType::KWORD_DO: return _SNOWBALL_KEYWORD__DO;
            case TokenType::KWORD_CLASS: return _SNOWBALL_KEYWORD__CLASS;
            case TokenType::KWORD_AS: return _SNOWBALL_KEYWORD__AS;
            case TokenType::KWORD_ENUM: return _SNOWBALL_KEYWORD__ENUM;
            case TokenType::KWORD_FUNC: return _SNOWBALL_KEYWORD__FUNCTION;
            case TokenType::KWORD_OPERATOR: return _SNOWBALL_KEYWORD__OPERATOR;
            case TokenType::KWORD_VAR: return _SNOWBALL_KEYWORD__VARIABLE;
            case TokenType::KWORD_CONST: return _SNOWBALL_KEYWORD__CONSTANT;
            case TokenType::KWORD_IF: return _SNOWBALL_KEYWORD__IF;
            case TokenType::KWORD_ELSE: return _SNOWBALL_KEYWORD__ELSE;
            case TokenType::KWORD_WHILE: return _SNOWBALL_KEYWORD__WHILE;
            case TokenType::KWORD_FOR: return _SNOWBALL_KEYWORD__FOR;
            case TokenType::KWORD_SWITCH: return _SNOWBALL_KEYWORD__SWITCH;
            case TokenType::KWORD_CASE: return _SNOWBALL_KEYWORD__CASE;
            case TokenType::KWORD_DEFAULT: return _SNOWBALL_KEYWORD__DEFAULT;
            case TokenType::KWORD_BREAK: return _SNOWBALL_KEYWORD__BREAK;
            case TokenType::KWORD_CONTINUE: return _SNOWBALL_KEYWORD__CONTINUE;
            case TokenType::KWORD_STATIC: return _SNOWBALL_KEYWORD__STATIC;
            case TokenType::KWORD_SUPER: return _SNOWBALL_KEYWORD__SUPER;
            case TokenType::KWORD_RETURN: return _SNOWBALL_KEYWORD__RETURN;
            case TokenType::KWORD_DECLTYPE: return _SNOWBALL_KEYWORD__DECLTYPE;
            case TokenType::KWORD_EXTERN: return _SNOWBALL_KEYWORD__EXTERN;
            case TokenType::KWORD_NEW: return _SNOWBALL_KEYWORD__NEW;
            case TokenType::KWORD_THROW: return _SNOWBALL_KEYWORD__THROW;
            case TokenType::KWORD_TRY: return _SNOWBALL_KEYWORD__TRY;
            case TokenType::KWORD_CATCH:
                return _SNOWBALL_KEYWORD__CATCH;

                // Literal values

            case TokenType::VALUE_NUMBER:
            case TokenType::VALUE_FLOAT:
            case TokenType::VALUE_BOOL: return value;

            case TokenType::VALUE_STRING: return std::string("\"") + value + "\"";
            case TokenType::VALUE_CHAR: return FMT("'%s'", value.c_str());

            // Other
            case TokenType::UNKNOWN: return "<unknown>";
            case TokenType::_EOF: return "<EOF>";

            default: return "<BUG>";
        }

        // TODO: throw error: missed enum in switch case
    }

    std::pair<int, int> get_pos() const { return std::pair<int, int>(std::make_pair(line, col)); }
    uint32_t get_width() const { return (uint32_t)to_string().size(); }
};
} // namespace snowball

#endif // __SNOWBALL_TOKEN_H_
