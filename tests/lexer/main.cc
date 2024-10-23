
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

TEST(LexerTest, LexerTripleChars) {
  auto lexer = frontend::Lexer::StartStringLexer("& && &=");
  auto token = lexer.GetNextToken();
  EXPECT_EQ(token.GetType(), frontend::TT::OpBitAnd);
  token = lexer.GetNextToken();
  EXPECT_EQ(token.GetType(), frontend::TT::OpAnd);
  token = lexer.GetNextToken();
  EXPECT_EQ(token.GetType(), frontend::TT::OpBitAndEq);
  token = lexer.GetNextToken();
  EXPECT_EQ(token.GetType(), frontend::TT::Eof);
}

TEST(LexerTest, LexerNumbers) {
  auto lexer = frontend::Lexer::StartStringLexer("123 456 789");
  auto token = lexer.GetNextToken();
  EXPECT_EQ(token.GetType(), frontend::TT::ValueNumber);
  EXPECT_EQ(token.GetValue(), "123");
  token = lexer.GetNextToken();
  EXPECT_EQ(token.GetType(), frontend::TT::ValueNumber);
  EXPECT_EQ(token.GetValue(), "456");
  token = lexer.GetNextToken();
  EXPECT_EQ(token.GetType(), frontend::TT::ValueNumber);
  EXPECT_EQ(token.GetValue(), "789");
  token = lexer.GetNextToken();
  EXPECT_EQ(token.GetType(), frontend::TT::Eof);
}
