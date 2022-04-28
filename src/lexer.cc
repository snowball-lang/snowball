
#include "lexer.h"
#include "token.h"
#include <string>

#define GET_CHAR(m_off) (                     \
    ((size_t)char_ptr + m_off >= _source_info->get_code().size()) \
        ? '\0'                                \
        : _source_info->get_code()[(size_t)char_ptr + m_off]      \
    )
#define EAT_CHAR(m_num)      \
    {                        \
        char_ptr += m_num;   \
	    cur_col += m_num;    \
    }
#define EAT_LINE()           \
    {	char_ptr++;          \
	    cur_col = 1;         \
	    cur_line++;          \
    }

namespace snowball {
    Lexer::Lexer(SourceInfo* p_source_info) {
        _source_info = p_source_info;
    }

    void Lexer::tokenize() {
        std::string code = _source_info->get_code();

        while (char_ptr < (int)code.size()) {
            tokenize_char();
        }
    }

    void Lexer::tokenize_char() {
        switch (GET_CHAR(0))
        {
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

            default:
                // TODO
                EAT_CHAR(1);
                break;
        }
    }

    void Lexer::handle_eof() {
        // Declare a new Token
        Token tk;

        // Fill al fields for the token
        // as an EOF type.
        tk.type = TokenType::_EOF;
        tk.line = cur_line;
        tk.col = cur_col;

        // Add token to the list of tokens
        _tokens.push_back(tk);
        EAT_CHAR(1);
    }

}
