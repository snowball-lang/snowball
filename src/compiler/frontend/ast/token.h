
#ifndef __SNOWBALL_FRONTEND_AST_TOKEN_H__
#define __SNOWBALL_FRONTEND_AST_TOKEN_H__

#include <string>

namespace snowball {
namespace frontend {

struct Token {
  enum Type {
    Identifier,

    ValueNumber, ValueFloat, ValueBool, ValueString, ValueChar,

    SymAt, SymDot, SymHash, SymComma, SymCollon, SymColcol, SymDollar, 
    SymQuestion, SymSemiCollon,
    
    BracketLcurly, BracketRcurly, BracketLparent, BracketRparent, 
    BracketRsquared, BracketLsquared,

    OpMul, OpMod, OpDiv, OpPlus, OpMinus,
    OpMuleq, OpDiveq, OpModEq, OpPluseq, OpMinuseq,
    OpGt, OpLt, OpArrow, OpEqeq, OpGteq, OpLteq, OpNoteq,
    OpEq, OpNot, OpAnd, OpOr,
    OpBitNot, OpBitOr, OpBitAnd, OpBitXor,
    OpBitOrEq, OpBitRshift, OpBitLshift, OpBitAndEq, OpBitXorEq, 
    OpBitRshiftEq, OpBitLshiftEq,
    
    KwordStartPoint, // This is a marker for the start of the keywords

    KwordIf, KwordVar, KwordNew, KwordThrow, KwordFor, KwordEnum, KwordFunc, 
    KwordOperator, KwordMacro, KwordElse, KwordBreak, KwordConst, KwordSuper, 
    KwordWhile, KwordExtern, KwordVirtual, KwordOverride, KwordClass, KwordAs, 
    KwordImport, KwordUnsafe, KwordConstexpr, KwordTypedef, KwordMutable, KwordDo, 
    KwordNamespace, KwordStruct, KwordPublic, KwordCase, KwordSwitch, KwordStatic, 
    KwordReturn, KwordPrivate, KwordDecltype, KwordDefault, KwordTry, KwordCatch, 
    KwordContinue, KwordInter, KwordExtends, KwordImplements, 
    
    KwordEndingPoint, // This is a marker for the end of the keywords
    
    Eof, Unknown
  };
// ---------------------
  std::string value = "";
  Type type = Type::Unknown;
  std::pair<unsigned int, unsigned int> location; // 1: line, 2: column
// ---------------------
  std::string to_string() const;
  unsigned int get_width() const; // Returns the width of the token
};

}
}

#endif // __SNOWBALL_AST_TOKEN_H__
