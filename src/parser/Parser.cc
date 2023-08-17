
#include "./Parser.h"

#include "../lexer/tokens/token.h"

namespace snowball {
namespace parser {

Parser::Parser(std::vector<Token> p_tokens, const SourceInfo* p_source_info)
    : m_tokens(p_tokens), m_source_info(p_source_info) {
  m_current = m_tokens.at(m_tok_index);
}

std::vector<Syntax::Node*> Parser::parse() { return parseGlobal(); }

Token Parser::next(int p_offset) {
  try {
    m_tok_index += (p_offset + 1);
    m_current = m_tokens.at(m_tok_index);

    return m_current;
  } catch (std::out_of_range& _) { createError<BUG>("Index error"); }

  return {};
}

Token Parser::prev(int p_offset, bool p_safe) {
  try {
    m_tok_index -= (p_offset + 1);
    m_current = m_tokens.at(m_tok_index);

    return m_current;
  } catch (std::out_of_range& _) {
    if (!p_safe) createError<BUG>("Index error");
  }

  return {};
}

Token Parser::peek(int p_offset, bool p_safe) {
  Token tmp = {TokenType::_EOF};
  if ((m_tok_index + 1) + p_offset < 0 || (m_tok_index + 1) + p_offset >= (int)m_tokens.size()) {
    if (p_safe)
      return tmp;
    else
      createError<BUG>("Parser::peek() index out of bounds");
  }

  return m_tokens.at((m_tok_index + 1) + p_offset);
}
} // namespace parser
} // namespace snowball
