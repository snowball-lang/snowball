
#include <gtest/gtest.h>
#include "frontend/lexer.h"

using namespace snowball;

TEST(LexerTest, SymbolLexing) {
  auto lexer = frontend::Lexer::StartStringLexer("+-*/");
  auto token = lexer.GetNextToken();
  EXPECT_EQ(token.GetType(), frontend::TT::OpPlus);
  token = lexer.GetNextToken();
  EXPECT_EQ(token.GetType(), frontend::TT::OpMinus);
  token = lexer.GetNextToken();
  EXPECT_EQ(token.GetType(), frontend::TT::OpMul);
  token = lexer.GetNextToken();
  EXPECT_EQ(token.GetType(), frontend::TT::OpDiv);
  token = lexer.GetNextToken();
  EXPECT_EQ(token.GetType(), frontend::TT::Eof);
}

TEST(LexerTest, LexerWithSpaces) {
  auto lexer = frontend::Lexer::StartStringLexer("  +\t-\n *\n\n\n \t / \t ");
  auto token = lexer.GetNextToken();
  EXPECT_EQ(token.GetType(), frontend::TT::OpPlus);
  token = lexer.GetNextToken();
  EXPECT_EQ(token.GetType(), frontend::TT::OpMinus);
  token = lexer.GetNextToken();
  EXPECT_EQ(token.GetType(), frontend::TT::OpMul);
  token = lexer.GetNextToken();
  EXPECT_EQ(token.GetType(), frontend::TT::OpDiv);
  token = lexer.GetNextToken();
  EXPECT_EQ(token.GetType(), frontend::TT::Eof);
}
