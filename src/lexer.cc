
#include "lexer.h"
#include "token.h"
#include "errors.h"

#include <string>

#define LEXER_ERROR(m_error, m_msg) throw SNError(m_error, std::string(m_msg));
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

            case '/':
			{
				if (GET_CHAR(1) == '/') { // comment

					while (GET_CHAR(0) != '\n' && GET_CHAR(0) != 0 ) {
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
							LEXER_ERROR(Error::UNEXPECTED_EOF, "");
						} else if (GET_CHAR(0) == '\n') {
							EAT_LINE();
						} else {
							EAT_CHAR(1);
						}
					}

				} else {
					if (GET_CHAR(1) == '=') consume(TokenType::OP_DIVEQ, 2);
					else consume(TokenType::OP_DIV);
				}
				break;
			}

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

    void Lexer::consume(TokenType p_tk, int p_eat_size) {
        Token tk;
        tk.type = p_tk;
        tk.line = cur_line;
        tk.col = cur_col;
        _tokens.push_back(tk);
        EAT_CHAR(p_eat_size);
    }

}
