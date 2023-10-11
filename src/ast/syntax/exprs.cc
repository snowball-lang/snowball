
#include "../errors/error.h"
#include "../types/Type.h"
#include "common.h"
#include "nodes.h"

#include <assert.h>
#include <string>
#include <vector>

namespace snowball {
namespace Syntax {
namespace Expression {

DeclType::DeclType(Base* value, DBGSourceInfo* srcInfo) : value(value), TypeRef("decltype(...)", srcInfo){};
FuncType::FuncType(std::vector<TypeRef*> args, TypeRef* returnValue, DBGSourceInfo* srcInfo)
    : args(args), returnValue(returnValue), TypeRef("fn(...)", srcInfo){};
ReferenceType::ReferenceType(TypeRef* baseType, DBGSourceInfo* srcInfo)
    : baseType(baseType), TypeRef(baseType->getName() + "&", srcInfo){};
PointerType::PointerType(TypeRef* baseType, bool isMutable, DBGSourceInfo* srcInfo)
    : baseType(baseType), TypeRef(baseType->getName() + "*", srcInfo) {
  setMutable(isMutable);
};
PseudoVariable::PseudoVariable(std::string identifier) : identifier(identifier){};
void PseudoVariable::setArgs(std::vector<Node*> args) {
  this->args = args;
  hasArguments = true;
}
bool PseudoVariable::hasArgs() const { return hasArguments; }
std::vector<Node*> PseudoVariable::getArgs() const { return args; }
TypeRef::TypeRef(Expression::Base* p_ast, std::string p_name, DBGSourceInfo* p_dbg, std::string id)
    : internalAST(p_ast), types::Type(REF, p_name), id(id) {
  setDBGInfo(p_dbg);
}
TypeRef::TypeRef(std::string p_name, snowball::DBGSourceInfo* p_dbg, std::vector<TypeRef*> p_generics, std::string id)
    : generics(p_generics), types::Type(REF, p_name), id(id) {
  setDBGInfo(p_dbg);
}
TypeRef::TypeRef(std::string p_name, DBGSourceInfo* p_dbg, types::Type* internalType, std::string id)
    : internalType(internalType), types::Type(REF, p_name), id(id) {
  setDBGInfo(p_dbg);
}
NewInstance::NewInstance(DBGSourceInfo* dbg, std::vector<Base*> args, TypeRef* ty) : type(ty) {
  auto call = Syntax::N<FunctionCall>(ty->toRef(), args);
  call->setDBGInfo(dbg);
  this->call = call;
}
void TypeRef::setGenerics(std::vector<TypeRef*> g) { generics = g; }
std::vector<Expression::TypeRef*> GenericIdentifier::getGenerics() const { return generics; }
std::vector<TypeRef*> TypeRef::getGenerics() { return this->generics; }
Param::Param(std::string name, TypeRef* type, Status generic) : name(name), type(type), status(generic) {
  assert(generic <= 1 && generic >= 0 && "Invalid param status");
} // clang-format off
bool BinaryOp::is_assignment(OpType opType) {
    return opType == OpType::EQ || opType == OpType::PLUSEQ ||
        opType == OpType::MINUSEQ ||
        opType == OpType::MULEQ || opType == OpType::DIVEQ ||
        opType == OpType::MOD_EQ ||
        opType == OpType::BIT_LSHIFT_EQ ||
        opType == OpType::BIT_RSHIFT_EQ ||
        opType == OpType::BIT_OR_EQ ||
        opType == OpType::BIT_AND_EQ ||
        opType == OpType::BIT_XOR_EQ;
}
bool BinaryOp::is_assignment(BinaryOp* p_node) {
    OpType p_op_type = p_node->op_type;
    return is_assignment(p_op_type);
}
bool BinaryOp::is_comp(OpType opType) {
    return opType == OpType::GT || opType == OpType::LT ||
        opType == OpType::GTEQ || opType == OpType::LTEQ ||
        opType == OpType::EQEQ || opType == OpType::NOTEQ;
}
std::string BinaryOp::to_string() const {
#define OP_CASE(op, symbol) case OpType::op: return symbol;
#define OP_DEFAULT default: assert(false);

    switch (op_type) {
        OP_CASE(GT, ">") OP_CASE(LT, "<")
        OP_CASE(GTEQ, ">=") OP_CASE(EQEQ, "==")
        OP_CASE(LTEQ, "<=") OP_CASE(NOTEQ, "!=")

        // Mathematical symbols
        OP_CASE(MOD, "%") OP_CASE(DIV, "/")
        OP_CASE(MUL, "*") OP_CASE(UPLUS, "+")
        OP_CASE(PLUS, "+") OP_CASE(MINUS, "-")
        OP_CASE(UMINUS, "-") OP_CASE(MULEQ, "*=")
        OP_CASE(DIVEQ, "/=") OP_CASE(PLUSEQ, "+=")
        OP_CASE(MOD_EQ, "%=") OP_CASE(MINUSEQ, "-=")

        OP_CASE(REFERENCE, "&")

        // Assignment
        OP_CASE(EQ, "=") OP_CASE(OR, "||")
        OP_CASE(AND, "&&") OP_CASE(NOT, "!")

        // Bitwise operations
        OP_CASE(BIT_OR, "|") OP_CASE(BIT_NOT, "~")
        OP_CASE(BIT_AND, "&") OP_CASE(BIT_XOR, "^")
        OP_CASE(BIT_OR_EQ, "|=") OP_CASE(BIT_LSHIFT, "<<")
        OP_CASE(BIT_RSHIFT, ">>") OP_CASE(BIT_AND_EQ, "&=")
        OP_CASE(BIT_XOR_EQ, "^=") OP_CASE(BIT_LSHIFT_EQ, "<<=")
        OP_CASE(BIT_RSHIFT_EQ, ">>=")

        OP_DEFAULT
    }
#undef OP_CASE
#undef OP_DEFAULT
} // clang-format on

std::string FunctionCall::getArgumentsAsString(const std::vector<types::Type*> args) {
  std::string result;
  int i = 0;
  for (auto arg = args.begin(); arg != args.end(); ++arg) {
    result += (*arg)->getPrettyName();
    if (i != args.size() - 1) { result += ", "; }
    i++;
  }

  return result;
}

std::string GenericIdentifier::getNiceName() const {
  std::string gens = "<";

  int gIndex = 0;
  for (auto t : generics) {
    gens += t->getPrettyName();
    if (gIndex != (generics.size() - 1)) { gens += ", "; }

    gIndex++;
  }

  return identifier + (gIndex > 0 ? gens + ">" : "");
}

#define CASE(t, r)                                                                                                     \
  case TokenType::t: return r;
ConstantValue::ConstantType ConstantValue::deduceType(TokenType ty) {
  switch (ty) {
    CASE(VALUE_STRING, String)
    CASE(VALUE_CHAR, Char)
    CASE(VALUE_FLOAT, Float)
    CASE(VALUE_NUMBER, Number)
    CASE(VALUE_BOOL, Bool)

    default: E<BUG>(FMT("Unknown token type, coudn't deduce! (ty: %i)", ty));
  }

  UNREACHABLE
}
#undef CASE

std::string TypeRef::getPrettyName() const {
  std::string gens = "<";

  int gIndex = 0;
  for (auto t : generics) {
    gens += t->getPrettyName();
    if (gIndex != (generics.size() - 1)) { gens += ", "; }

    gIndex++;
  }

  return getName() + (gIndex > 0 ? gens + ">" : "");
}

} // namespace Expression

std::string Macro::arguementTypeToString(Macro::ArguementType t) {
  switch (t) {
    case Macro::ArguementType::CONSTANT: return "constant";
    case Macro::ArguementType::EXPRESSION: return "expression";
    case Macro::ArguementType::STATEMENT: return "statement";
    case Macro::ArguementType::CONSTANT_STRING: return "constant string";
    case Macro::ArguementType::CONSTANT_NUMBER: return "constant number";
    case Macro::ArguementType::CONSTANT_CHAR: return "constant char";
    case Macro::ArguementType::TYPE: return "type";
    default: E<BUG>(FMT("Unknown arguement type '%i'!", t));
  }

  UNREACHABLE
}

} // namespace Syntax
} // namespace snowball
