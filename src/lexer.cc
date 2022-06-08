
#include "snowball/lexer.h"
#include "snowball/token.h"
#include "snowball/errors.h"

#include <string>
#include <vector>

#define GET_CHAR(m_off) (                     \
    ((size_t)char_ptr + m_off >= _source_info->get_source().size()) \
        ? '\0'                                \
        : _source_info->get_source()[(size_t)char_ptr + m_off]      \
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

#define IS_NUM(c) ( \
    (               \
        '0' <= c && \
        c <= '9'    \
        )           \
    )

#define IS_HEX_CHAR(c)   \
( IS_NUM(c) || ('a' <= c && c <= 'f') || ('A' <= c && c <= 'F') )

#define IS_TEXT(c)       \
( (c == '_') || ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') )



namespace snowball {
	/*=======================================
   	 * Lexer constructor. used to set some
	 * variables to the Lexer class.
	 *
	 * @params: SourceInfo* p_source_info
	 *=======================================*/
    Lexer::Lexer(SourceInfo* p_source_info) {
        _source_info = p_source_info;
    }

	/*=======================================
   	 * Convert the source code into an array
	 * of tokens.
	 *=======================================*/
    void Lexer::tokenize() {
        std::string code = _source_info->get_source();

		if ((int)code.size() == 0)return;

		// Iterate every character of the source code
		// and tokenize that char. Tokenizing it will
		// mean that respective Token for the current
		// char will also be added to the Token array
        while (char_ptr < (int)code.size()) {
            tokenize_char();
        }

		// For some reason, sometimes the tokenizer
		// does not detect the end of the source code.
		// that is why we add a Token with _EOF type to
		// the Token array (for later use in the parser)
		if ((*tokens.end()).type != TokenType::_EOF) {

			// add "false" as a param for "p_consume"
			// so that the lexer does not "consume"
			handle_eof(false);
		}
    }

	/*=======================================
   	 * Tokenize the current character and add
	 * it to the Token's array
	 *
	 * note: this is called after each
	 * 	iteration of Lexer::tokenize()
	 *=======================================*/
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

					// Skip characters until we encounter _EOF or NEW_LINE
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
							lexer_error(Error::UNEXPECTED_EOF, "Found an unexpected EOF while parsing a comment", 1);
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

			// symbols
			case ',': consume(TokenType::SYM_COMMA); break;
			case ':': consume(TokenType::SYM_COLLON); break;
			case ';': consume(TokenType::SYM_SEMI_COLLON); break;
			case '@': consume(TokenType::SYM_AT); break;
			case '#': consume(TokenType::SYM_HASH); break;
			case '$': consume(TokenType::SYM_DOLLAR); break;
			case '?': consume(TokenType::SYM_QUESTION); break;

			// brackets
			case '(': consume(TokenType::BRACKET_LPARENT); break;
			case ')': consume(TokenType::BRACKET_RPARENT); break;
			case '{': consume(TokenType::BRACKET_LCURLY); break;
			case '}': consume(TokenType::BRACKET_RCURLY); break;
			case '[': consume(TokenType::BRACKET_LSQUARED); break;
			case ']': consume(TokenType::BRACKET_RSQUARED); break;

			// op
			case '=': {
				if (GET_CHAR(1) == '=') consume(TokenType::OP_EQEQ, 2);
				else consume(TokenType::OP_EQ);
				break;
			}
			case '+': {
				if (GET_CHAR(1) == '=') consume(TokenType::OP_PLUSEQ, 2);
				else consume(TokenType::OP_PLUS);
				break;
			}
			case '-': {
				if (GET_CHAR(1) == '=') consume(TokenType::OP_MINUSEQ, 2);
				else consume(TokenType::OP_MINUS);
				break;
			}
			case '*': {
				if (GET_CHAR(1) == '=') consume(TokenType::OP_MULEQ, 2);
				else consume(TokenType::OP_MUL);
				break;
			}
			case '\\':
				lexer_error(Error::SYNTAX_ERROR, "invalid character '\\'.", 1);
				break;
			case '%': {
				if (GET_CHAR(1) == '=') consume(TokenType::OP_MOD_EQ, 2);
				else consume(TokenType::OP_MOD);
				break;
			}
			case '<': {
				if (GET_CHAR(1) == '=') consume(TokenType::OP_LTEQ, 2);
				else if (GET_CHAR(1) == '<') {
					if (GET_CHAR(2) == '=') consume(TokenType::OP_BIT_LSHIFT_EQ, 3);
					else consume(TokenType::OP_BIT_LSHIFT, 2);
				}
				else consume(TokenType::OP_LT);
				break;
			}
			case '>': {
				if (GET_CHAR(1) == '=') consume(TokenType::OP_GTEQ, 2);
				else if (GET_CHAR(1) == '>') {
					if (GET_CHAR(2) == '=') consume(TokenType::OP_BIT_RSHIFT_EQ, 3);
					else consume(TokenType::OP_BIT_RSHIFT, 2);
				}
				else consume(TokenType::OP_GT);
				break;
			}
			case '!': {
				if (GET_CHAR(1) == '=') consume(TokenType::OP_NOTEQ, 2);
				else consume(TokenType::OP_NOT);
				break;
			}
			case '~':
				consume(TokenType::OP_BIT_NOT);
				break;
			case '|': {
				if (GET_CHAR(1) == '=') consume(TokenType::OP_BIT_OR_EQ, 2);
				else if (GET_CHAR(1) == '|') consume(TokenType::OP_OR, 2);
				else consume(TokenType::OP_BIT_OR);
				break;
			}
			case '&': {
				if (GET_CHAR(1) == '=') consume(TokenType::OP_BIT_AND_EQ, 2);
				else if (GET_CHAR(1) == '&') consume(TokenType::OP_AND, 2);
				else consume(TokenType::OP_BIT_AND);
				break;
			}
			case '^': {
				if (GET_CHAR(1) == '=') consume(TokenType::OP_BIT_XOR_EQ, 2);
				else consume(TokenType::OP_BIT_XOR);
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
								lexer_error(Error::UNEXPECTED_EOF, "unexpected EOF while parsing a String scape.");
								break;
							case '\\': str += '\\'; EAT_CHAR(2); break;
							case '\'': str += '\''; EAT_CHAR(2); break;
							case 't':  str += '\t'; EAT_CHAR(2); break;
							case 'n':  str += '\n'; EAT_CHAR(2); break;
							case '"':  str += '"';  EAT_CHAR(2); break;
							case 'r':  str += '\r'; EAT_CHAR(2); break;
							case '\n': EAT_CHAR(1); EAT_LINE(); break;
							default:
								lexer_error(Error::SYNTAX_ERROR, "invalid escape character", 2);
						}
					} else if (GET_CHAR(0) == 0) {
						lexer_error(Error::UNEXPECTED_EOF, "unexpected EOF while parsing String.");
						break;
					} else {
						str += GET_CHAR(0);
						if (GET_CHAR(0) == '\n') { EAT_LINE(); }
						else { EAT_CHAR(1); }
					}
				}
				EAT_CHAR(1);

				Token tk;
				tk.type = TokenType::VALUE_STRING;
				tk.value = str; // method name may be builtin func
				tk.col = cur_col - ((int)str.size() + (2 /* speech marks */));
				tk.line = cur_line;
				tokens.emplace_back(tk);

				break;
			}

            default:
				// TODO: 1.2e3 => is a valid float number

				// float value begins with '.'
				if (GET_CHAR(0) == '.' && IS_NUM(GET_CHAR(1)) ) {
					std::string float_str(1, '.');
					EAT_CHAR(1);
					while (IS_NUM(GET_CHAR(0))) {
						float_str += GET_CHAR(0);
						EAT_CHAR(1);
					}

					double float_val = std::stod(float_str);
                    Token tk;
                    tk.type = TokenType::VALUE_FLOAT;
                    tk.line = cur_line;
                    tk.col = cur_col - (int)sizeof(float_str);
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
						if (GET_CHAR(1) == 'b' || GET_CHAR(1) == 'B') mode = BIN;
						if (GET_CHAR(1) == 'x' || GET_CHAR(1) == 'X') mode = HEX;
					}
					EAT_CHAR(1);
					switch (mode) {
						case INT: {
							while (IS_NUM(GET_CHAR(0)) || GET_CHAR(0) == '.') {
								if (GET_CHAR(0) == '.' && mode == FLOAT)
									lexer_error(Error::SYNTAX_ERROR, "invalid numeric value.", 1);
								if (GET_CHAR(0) == '.')
									mode = FLOAT;
								num += GET_CHAR(0);
								EAT_CHAR(1);
							}
						} break;
						case BIN: {
							num += GET_CHAR(0); EAT_CHAR(1); // eat 'b';
							while (GET_CHAR(0) == '0' || GET_CHAR(0) == '1') {
								num += GET_CHAR(0);
								EAT_CHAR(1);
							}
						} break;
						case HEX: {
							num += GET_CHAR(0); EAT_CHAR(1); // eat 'x';
							while (IS_HEX_CHAR(GET_CHAR(0))) {
								num += GET_CHAR(0);
								EAT_CHAR(1);
							}
						} break;

						default:
							lexer_error(Error::BUG, Logger::format("Unreachable number mode \"%i\"", mode), num.size());
					}

					// "1." parsed as 1.0 which should be error.
					if (num[num.size()-1] == '.') lexer_error(Error::SYNTAX_ERROR, "invalid numeric value.");

                    Token tk;
                    tk.line = cur_line;
                    tk.col = cur_col - (int)sizeof(num);
                    tk.value = num;
					if (mode == FLOAT){
                        tk.type = TokenType::VALUE_FLOAT;}
					else{
	                    tk.type = TokenType::VALUE_NUMBER;}

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
					tk.col = cur_col - (int)identifier.size();
					tk.line = cur_line;

					if (identifier == "null") 		   { tk.type = TokenType::VALUE_NULL;						}
					else if (identifier == "or")       { tk.type = TokenType::OP_OR; 							}
					else if (identifier == "and")      { tk.type = TokenType::OP_AND; 						  	}
					else if (identifier == "not")  	   { tk.type = TokenType::OP_NOT; 						  	}

					else if (identifier == "if")	   { tk.type = TokenType::KWORD_IF;							}
					else if (identifier == "var")	   { tk.type = TokenType::KWORD_VAR;						}
					else if (identifier == "for")	   { tk.type = TokenType::KWORD_FOR;						}
					else if (identifier == "enum")	   { tk.type = TokenType::KWORD_ENUM;						}
					else if (identifier == "this")	   { tk.type = TokenType::KWORD_THIS;						}
					else if (identifier == "case")	   { tk.type = TokenType::KWORD_CASE;						}
					else if (identifier == "func")	   { tk.type = TokenType::KWORD_FUNC;						}
					else if (identifier == "else")	   { tk.type = TokenType::KWORD_ELSE;						}
					else if (identifier == "class")	   { tk.type = TokenType::KWORD_CLASS;						}
					else if (identifier == "const")	   { tk.type = TokenType::KWORD_CONST;						}
					else if (identifier == "while")	   { tk.type = TokenType::KWORD_WHILE;						}
					else if (identifier == "super")	   { tk.type = TokenType::KWORD_SUPER;						}
					else if (identifier == "switch")   { tk.type = TokenType::KWORD_SWITCH;						}
					else if (identifier == "static")   { tk.type = TokenType::KWORD_STATIC;						}
					else if (identifier == "import")   { tk.type = TokenType::KWORD_IMPORT;						}
					else if (identifier == "return")   { tk.type = TokenType::KWORD_RETURN;						}
					else if (identifier == "default")  { tk.type = TokenType::KWORD_DEFAULT;					}
					else if (identifier == "continue") { tk.type = TokenType::KWORD_CONTINUE;					}
					else if (identifier == "undefined"){ tk.type = TokenType::VALUE_UNDEFINED;					}

					else if (identifier == "true" || identifier == "false") { tk.type = TokenType::VALUE_BOOL;	}
					else {
						tk.type = TokenType::IDENTIFIER;
					}

					tokens.emplace_back(tk);
					break;
				}


				if (GET_CHAR(0) == '.') {
					consume(TokenType::SYM_DOT);
					break;
				}

				lexer_error(Error::SYNTAX_ERROR, Logger::format("unknown character '%c' in parsing.", GET_CHAR(0)), 1);
            }
    }

	/*=======================================
   	 * Add Token to the array with type _EOF
	 * and consume that token if "p_consume"
	 * is set to true.
	 *=======================================*/
    void Lexer::handle_eof(bool p_consume) {
        // Declare a new Token
        Token tk;

        // Fill al fields for the token
        // as an EOF type.
        tk.type = TokenType::_EOF;
        tk.line = cur_line;
        tk.col = cur_col;

        // Add token to the list of tokens
        tokens.emplace_back(tk);

		if (p_consume) {
	        EAT_CHAR(1);
		}
    }

	/*=======================================
   	 * Create a new token and add it to the
	 * Token array. We will also consume that
	 * character.
	 *=======================================*/
    void Lexer::consume(TokenType p_tk, int p_eat_size) {
        Token tk;
        tk.type = p_tk;
        tk.line = cur_line;
        tk.col = cur_col;
        tokens.emplace_back(tk);
        EAT_CHAR(p_eat_size);
    }

	/*=======================================
   	 * Used to create a new Debug Source Info
	 * and throw a new LexerError.
	 *=======================================*/
    void Lexer::lexer_error(Error m_error, std::string m_msg, int char_length) {
        DBGSourceInfo* dbg_info = new DBGSourceInfo((SourceInfo*)_source_info, std::pair<int, int>(cur_line, cur_col), char_length);
        throw LexerError(m_error, std::string(m_msg), dbg_info);
    }
}
