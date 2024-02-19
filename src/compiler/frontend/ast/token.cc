
#include "compiler/frontend/ast/token.h"
#include "compiler/frontend/ast/kwords.def"

namespace snowball {
namespace frontend {

unsigned int Token::get_width() const { 
  switch (type) {
    case Type::Eof: 
    case Type::Unknown:
      return 1;
    default: 
      return this->to_string().size(); 
  }
}
std::string Token::to_string() const {
  switch (type) {
    // Symbols
    case Type::SymAt: return "@";
    case Type::SymDot: return ".";
    case Type::SymHash: return "#";
    case Type::SymComma: return ",";
    case Type::SymCollon: return ":";
    case Type::SymDollar: return "$";
    case Type::SymQuestion: return "?";
    case Type::SymSemiCollon: return ";";
    case Type::SymColcol: return "::";
    // Brackets
    case Type::BracketLcurly: return "{";
    case Type::BracketRcurly: return "}";
    case Type::BracketLparent: return "(";
    case Type::BracketRparent: return ")";
    case Type::BracketLsquared: return "[";
    case Type::BracketRsquared: return "]";
    // Equiality
    case Type::OpGt: return ">";
    case Type::OpLt: return "<";
    case Type::OpGteq: return ">=";
    case Type::OpEqeq: return "==";
    case Type::OpLteq: return "<=";
    case Type::OpNoteq: return "!=";
    case Type::OpArrow: return "=>";
    // Mathematical symbols
    case Type::OpMod: return "%";
    case Type::OpDiv: return "/";
    case Type::OpMul: return "*";
    case Type::OpPlus: return "+";
    case Type::OpMinus: return "-";
    case Type::OpMuleq: return "*=";
    case Type::OpDiveq: return "/=";
    case Type::OpPluseq: return "+=";
    case Type::OpModEq: return "%=";
    case Type::OpMinuseq: return "-=";
    // Asignment
    case Type::OpEq: return "=";
    case Type::OpOr: return "||";
    case Type::OpAnd: return "&&";
    case Type::OpNot: return "!";
    // Bitwise operations
    case Type::OpBitOr: return "|";
    case Type::OpBitNot: return "~";
    case Type::OpBitAnd: return "&";
    case Type::OpBitXor: return "^";
    case Type::OpBitOrEq: return "|=";
    case Type::OpBitLshift: return "<<";
    case Type::OpBitRshift: return "|>>";
    case Type::OpBitAndEq: return "&=";
    case Type::OpBitXorEq: return "^=";
    case Type::OpBitLshiftEq: return "<<=";
    case Type::OpBitRshiftEq: return ">>=";
    // Identifiers
    case Type::Identifier: return value;
    // Keywods
    case Type::KwordPublic: return SN_KEYWORD_PUBLIC;
    case Type::KwordVirtual: return SN_KEYWORD_VIRTUAL;
    case Type::KwordOverride: return SN_KEYWORD_OVERRIDE;
    case Type::KwordPrivate: return SN_KEYWORD_PRIVATE;
    case Type::KwordImport: return SN_KEYWORD_IMPORT;
    case Type::KwordUnsafe: return SN_KEYWORD_UNSAFE;
    case Type::KwordConstexpr: return SN_KEYWORD_CONSTEXPR;
    case Type::KwordNamespace: return SN_KEYWORD_NAMESPACE;
    case Type::KwordStruct: return SN_KEYWORD_STRUCT;
    case Type::KwordTypedef: return SN_KEYWORD_TYPEDEF;
    case Type::KwordMutable: return SN_KEYWORD_MUTABLE;
    case Type::KwordDo: return SN_KEYWORD_DO;
    case Type::KwordClass: return SN_KEYWORD_CLASS;
    case Type::KwordAs: return SN_KEYWORD_AS;
    case Type::KwordEnum: return SN_KEYWORD_ENUM;
    case Type::KwordFunc: return SN_KEYWORD_FUNCTION;
    case Type::KwordMacro: return SN_KEYWORD_MACRO;
    case Type::KwordOperator: return SN_KEYWORD_OPERATOR;
    case Type::KwordVar: return SN_KEYWORD_VARIABLE;
    case Type::KwordConst: return SN_KEYWORD_CONSTANT;
    case Type::KwordIf: return SN_KEYWORD_IF;
    case Type::KwordElse: return SN_KEYWORD_ELSE;
    case Type::KwordWhile: return SN_KEYWORD_WHILE;
    case Type::KwordFor: return SN_KEYWORD_FOR;
    case Type::KwordCase: return SN_KEYWORD_CASE;
    case Type::KwordSwitch: return SN_KEYWORD_SWITCH;
    case Type::KwordDefault: return SN_KEYWORD_DEFAULT;
    case Type::KwordBreak: return SN_KEYWORD_BREAK;
    case Type::KwordContinue: return SN_KEYWORD_CONTINUE;
    case Type::KwordStatic: return SN_KEYWORD_STATIC;
    case Type::KwordSuper: return SN_KEYWORD_SUPER;
    case Type::KwordReturn: return SN_KEYWORD_RETURN;
    case Type::KwordDecltype: return SN_KEYWORD_DECLTYPE;
    case Type::KwordExtern: return SN_KEYWORD_EXTERN;
    case Type::KwordNew: return SN_KEYWORD_NEW;
    case Type::KwordThrow: return SN_KEYWORD_THROW;
    case Type::KwordTry: return SN_KEYWORD_TRY;
    case Type::KwordInter: return SN_KEYWORD_INTER;
    case Type::KwordExtends: return SN_KEYWORD_EXTENDS;
    case Type::KwordImplements: return SN_KEYWORD_IMPLS;
    case Type::KwordCatch: return SN_KEYWORD_CATCH;
    // Literal values
    case Type::ValueNumber:
    case Type::ValueFloat:
    case Type::ValueBool: return value;
    case Type::ValueString: return std::string("\"") + value + "\"";
    case Type::ValueChar: return std::string("'") + value + "'";
    // Other
    case Type::Unknown: return "<unknown>";
    case Type::Eof: return "<EOF>";
    default: return "<BUG>";
  }
}

}
}
