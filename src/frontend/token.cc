
#include "frontend/token.h"

namespace snowball::frontend {

SNOWBALL_NO_DISCARD auto Token::GetLength() const -> u16 {
  switch (mType) {
    case TT::Unknown:
    case TT::Eof:
      return 1;
    default:
      return SnowballFormat(*this).size();
  }
}

auto SnowballFormat(const Token& token) -> String {
  switch (token.GetType()) {
    case TT::SymAt: return "@";
    case TT::SymDot: return ".";
    case TT::SymHash: return "#";
    case TT::SymComma: return ",";
    case TT::SymColon: return ":";
    case TT::SymDollar: return "$";
    case TT::SymQuestion: return "?";
    case TT::SymSemiColon: return ";";
    case TT::SymColcol: return "::";
    
    case TT::BracketLcurly: return "{";
    case TT::BracketRcurly: return "}";
    case TT::BracketLparent: return "(";
    case TT::BracketRparent: return ")";
    case TT::BracketLsquared: return "[";
    case TT::BracketRsquared: return "]";
    
    case TT::OpGt: return ">";
    case TT::OpLt: return "<";
    case TT::OpGteq: return ">=";
    case TT::OpEqeq: return "==";
    case TT::OpLteq: return "<=";
    case TT::OpNoteq: return "!=";
    case TT::OpArrow: return "=>";
    
    case TT::OpMod: return "%";
    case TT::OpDiv: return "/";
    case TT::OpMul: return "*";
    case TT::OpPlus: return "+";
    case TT::OpMinus: return "-";
    case TT::OpMuleq: return "*=";
    case TT::OpDiveq: return "/=";
    case TT::OpPluseq: return "+=";
    case TT::OpModeq: return "%=";
    case TT::OpMinuseq: return "-=";
    
    case TT::OpEq: return "=";
    case TT::OpOr: return "||";
    case TT::OpAnd: return "&&";
    case TT::OpNot: return "!";
    
    case TT::OpBitOr: return "|";
    case TT::OpBitNot: return "~";
    case TT::OpBitAnd: return "&";
    case TT::OpBitXor: return "^";
    case TT::OpBitOrEq: return "|=";
    case TT::OpBitLshift: return "<<";
    case TT::OpBitRshift: return "|>>";
    case TT::OpBitAndEq: return "&=";
    case TT::OpBitXorEq: return "^=";
    case TT::OpBitLshiftEq: return "<<=";
    case TT::OpBitRshiftEq: return ">>=";
    
    case TT::Identifier: return token.GetValue();
    
    case TT::KwordPublic: return "public";
    case TT::KwordVirtual: return "virtual";
    case TT::KwordOverride: return "override";
    case TT::KwordPrivate: return "private";
    case TT::KwordUse: return "import";
    case TT::KwordUnsafe: return "unsafe";
    case TT::KwordNamespace: return "namespace";
    case TT::KwordTypedef: return "type";
    case TT::KwordMutable: return "mutable";
    case TT::KwordDo: return "do";
    case TT::KwordClass: return "class";
    case TT::KwordAs: return "as";
    case TT::KwordEnum: return "enum";
    case TT::KwordFunc: return "func";
    case TT::KwordMacro: return "macro";
    case TT::KwordOperator: return "operator";
    case TT::KwordVar: return "let";
    case TT::KwordConst: return "const";
    case TT::KwordIf: return "if";
    case TT::KwordElse: return "else";
    case TT::KwordWhile: return "while";
    case TT::KwordFor: return "for";
    case TT::KwordCase: return "case";
    case TT::KwordSwitch: return "match";
    case TT::KwordDefault: return "default";
    case TT::KwordBreak: return "break";
    case TT::KwordContinue: return "continue";
    case TT::KwordStatic: return "static";
    case TT::KwordSuper: return "super";
    case TT::KwordReturn: return "return";
    case TT::KwordAbstract: return "abstract";
    case TT::KwordFinal: return "final";
    case TT::KwordInline: return "inline";
    case TT::KwordExtern: return "extern";
    case TT::KwordDelete: return "delete";
    case TT::KwordThrow: return "throw";
    case TT::KwordTry: return "try";
    case TT::KwordInter: return "interface";
    case TT::KwordExtends: return "extends";
    case TT::KwordImplements: return "implements";
    case TT::KwordCatch: return "catch";
    
    case TT::ValueNumber:
    case TT::ValueFloat:
    case TT::ValueBool: 
      return token.GetValue();
    case TT::ValueString: 
      return String("\"") + token.GetValue() + "\"";
    case TT::ValueChar: 
      return String("'") + token.GetValue() + "'";
    
    case TT::Eof: return "<EOF>";

    case TT::Unknown:
    default: return "<unknown>";
  }
}

}; // namespace snowball::frontend