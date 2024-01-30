
#include "Parser.h"

#include <assert.h>

namespace snowball {
namespace parser {

using namespace Syntax;

Syntax::Statement::LoopFlow* Parser::parseLoopControl() {
  assert(is<TokenType::KWORD_BREAK>() || is<TokenType::KWORD_CONTINUE>());
  Statement::LoopFlow::FlowType type;
  switch (m_current.type) {
    case TokenType::KWORD_BREAK: type = Statement::LoopFlow::FlowType::Break; break;
    case TokenType::KWORD_CONTINUE: type = Statement::LoopFlow::FlowType::Continue; break;
    default: assert(false);
  }
  if (!m_inside_loop) {
    createError<SYNTAX_ERROR>("Cannot use loop control outside of a loop!", {
      .info = "Not inside a loop",
      .note = "You can only use loop control statements inside of a loop"
    });
  }
  auto dbg = DBGSourceInfo::fromToken(m_source_info, m_current);
  auto flow = N<Statement::LoopFlow>(type);
  flow->setDBGInfo(dbg);
  return flow;
}

} // namespace parser
} // namespace snowball
