
#include "errors.h"
#include "logger.h"
#include "source_info.h"
#include "token.h"

#include <vector>

#ifndef __SNOWBALL_LEXER_H_
#define __SNOWBALL_LEXER_H_

namespace snowball {
/**
 * @brief Tokenizer class
 *
 * The lexer transforms the source code into an
 * array of `tokens` that can be used for later parsing.
 *
 * We use tokens because it allows us to parse more easily our
 * privided source code. We dont need to worry about white spaces,
 * new lines, tabs and overall, very specific situations that will
 * create some bugs if they are not handled properly, creating a very
 * bad parser.
 *
 * It also facilitates us because each token contains source information
 * such as location and line numbers.
 */
class Lexer {
  public:
    Lexer(SourceInfo *p_source_info);

    void tokenize();
    std::vector<Token> tokens;

    ~Lexer(){};

  private:
    // methods
    void tokenize_char();
    void handle_eof(bool p_consume = true);
    void consume(TokenType p_tk, int p_eat_size = 1);
    void lexer_error(Error m_error, std::string m_msg, int char_length = 1,
                     const std::string& info = "");

    // vars
    SourceInfo *_source_info;

    int cur_line = 1;
    int cur_col  = 1;

    int char_ptr = 0;
};
} // namespace snowball

#endif // __SNOWBALL_LEXER_H_
