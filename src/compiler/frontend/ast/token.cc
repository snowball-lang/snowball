
#include "compiler/frontend/ast/token.h"
#include "compiler/frontend/ast/kwords.h"

namespace snowball {
namespace frontend {

unsigned int Token::get_width() const { return this->to_string().size(); }
std::string Token::to_string() const {
  switch (type) {
    // Symbols
    case TokenType::SymAt: return "@";
    case TokenType::SymDot: return ".";
    case TokenType::SymHash: return "#";
    case TokenType::SymComma: return ",";
    case TokenType::SymCollon: return ":";
    case TokenType::SymDollar: return "$";
    case TokenType::SymQuestion: return "?";
    case TokenType::SymSemiCollon: return ";";
    case TokenType::SymColcol: return "::";
    // Brackets
    case TokenType::BracketLcurly: return "{";
    case TokenType::BracketRcurly: return "}";
    case TokenType::BracketLparent: return "(";
    case TokenType::BracketRparent: return ")";
    case TokenType::BracketLsquared: return "[";
    case TokenType::BracketRsquared: return "]";
    // Equiality
    case TokenType::OpGt: return ">";
    case TokenType::OpLt: return "<";
    case TokenType::OpGteq: return ">=";
    case TokenType::OpEqeq: return "==";
    case TokenType::OpLteq: return "<=";
    case TokenType::OpNoteq: return "!=";
    case TokenType::OpArrow: return "=>";
    // Mathematical symbols
    case TokenType::OpMod: return "%";
    case TokenType::OpDiv: return "/";
    case TokenType::OpMul: return "*";
    case TokenType::OpPlus: return "+";
    case TokenType::OpMinus: return "-";
    case TokenType::OpMuleq: return "*=";
    case TokenType::OpDiveq: return "/=";
    case TokenType::OpPluseq: return "+=";
    case TokenType::OpModEq: return "%=";
    case TokenType::OpMinuseq: return "-=";
    // Asignment
    case TokenType::OpEq: return "=";
    case TokenType::OpOr: return "||";
    case TokenType::OpAnd: return "&&";
    case TokenType::OpNot: return "!";
    // Bitwise operations
    case TokenType::OpBitOr: return "|";
    case TokenType::OpBitNot: return "~";
    case TokenType::OpBitAnd: return "&";
    case TokenType::OpBitXor: return "^";
    case TokenType::OpBitOrEq: return "|=";
    case TokenType::OpBitLshift: return "<<";
    case TokenType::OpBitRshift: return "|>>";
    case TokenType::OpBitAndEq: return "&=";
    case TokenType::OpBitXorEq: return "^=";
    case TokenType::OpBitLshiftEq: return "<<=";
    case TokenType::OpBitRshiftEq: return ">>=";
    // Identifiers
    case TokenType::Identifier: return value;
    // Keywods
    case TokenType::KwordPublic: return SN_KEYWORD_PUBLIC;
    case TokenType::KwordVirtual: return SN_KEYWORD_VIRTUAL;
    case TokenType::KwordOverride: return SN_KEYWORD_OVERRIDE;
    case TokenType::KwordPrivate: return SN_KEYWORD_PRIVATE;
    case TokenType::KwordImport: return SN_KEYWORD_IMPORT;
    case TokenType::KwordUnsafe: return SN_KEYWORD_UNSAFE;
    case TokenType::KwordConstexpr: return SN_KEYWORD_CONSTEXPR;
    case TokenType::KwordNamespace: return SN_KEYWORD_NAMESPACE;
    case TokenType::KwordStruct: return SN_KEYWORD_STRUCT;
    case TokenType::KwordTypedef: return SN_KEYWORD_TYPEDEF;
    case TokenType::KwordMutable: return SN_KEYWORD_MUTABLE;
    case TokenType::KwordDo: return SN_KEYWORD_DO;
    case TokenType::KwordClass: return SN_KEYWORD_CLASS;
    case TokenType::KwordAs: return SN_KEYWORD_AS;
    case TokenType::KwordEnum: return SN_KEYWORD_ENUM;
    case TokenType::KwordFunc: return SN_KEYWORD_FUNCTION;
    case TokenType::KwordMacro: return SN_KEYWORD_MACRO;
    case TokenType::KwordOperator: return SN_KEYWORD_OPERATOR;
    case TokenType::KwordVar: return SN_KEYWORD_VARIABLE;
    case TokenType::KwordConst: return SN_KEYWORD_CONSTANT;
    case TokenType::KwordIf: return SN_KEYWORD_IF;
    case TokenType::KwordElse: return SN_KEYWORD_ELSE;
    case TokenType::KwordWhile: return SN_KEYWORD_WHILE;
    case TokenType::KwordFor: return SN_KEYWORD_FOR;
    case TokenType::KwordCase: return SN_KEYWORD_CASE;
    case TokenType::KwordSwitch: return SN_KEYWORD_SWITCH;
    case TokenType::KwordDefault: return SN_KEYWORD_DEFAULT;
    case TokenType::KwordBreak: return SN_KEYWORD_BREAK;
    case TokenType::KwordContinue: return SN_KEYWORD_CONTINUE;
    case TokenType::KwordStatic: return SN_KEYWORD_STATIC;
    case TokenType::KwordSuper: return SN_KEYWORD_SUPER;
    case TokenType::KwordReturn: return SN_KEYWORD_RETURN;
    case TokenType::KwordDecltype: return SN_KEYWORD_DECLTYPE;
    case TokenType::KwordExtern: return SN_KEYWORD_EXTERN;
    case TokenType::KwordNew: return SN_KEYWORD_NEW;
    case TokenType::KwordThrow: return SN_KEYWORD_THROW;
    case TokenType::KwordTry: return SN_KEYWORD_TRY;
    case TokenType::KwordInter: return SN_KEYWORD_INTER;
    case TokenType::KwordExtends: return SN_KEYWORD_EXTENDS;
    case TokenType::KwordImplements: return SN_KEYWORD_IMPLS;
    case TokenType::KwordCatch: return SN_KEYWORD_CATCH;
    // Literal values
    case TokenType::ValueNumber:
    case TokenType::ValueFloat:
    case TokenType::ValueBool: return value;
    case TokenType::ValueString: return std::string("\"") + value + "\"";
    case TokenType::ValueChar: return FMT("'%s'", value.c_str());
    // Other
    case TokenType::Unknown: return "<unknown>";
    case TokenType::Eof: return "<EOF>";
    default: return "<BUG>";
  }
}

}
}
