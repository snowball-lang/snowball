
#include "../errors/error.h"
#include "common.h"
#include "nodes.h"

#include <assert.h>
#include <string>
#include <vector>

namespace snowball {
namespace Syntax {
namespace Expression {

DeclType::DeclType(Base *value, DBGSourceInfo *srcInfo)
    : value(value), TypeRef("$decltype", srcInfo){};
PseudoVariable::PseudoVariable(std::string identifier)
    : identifier(identifier){};
TypeRef::TypeRef(std::string p_name, snowball::DBGSourceInfo *p_dbg,
                 std::vector<TypeRef *> p_generics)
    : generics(p_generics), types::Type(REF, p_name) {
    setDBGInfo(p_dbg);
}
TypeRef::TypeRef(std::string p_name, DBGSourceInfo *p_dbg,
            std::shared_ptr<types::Type> internalType)
    : internalType(internalType), types::Type(REF, p_name)
    {setDBGInfo(p_dbg);}
void TypeRef::setGenerics(std::vector<TypeRef *> g) { generics = g; }
std::vector<Expression::TypeRef *> GenericIdentifier::getGenerics() const {
    return generics;
}
std::vector<TypeRef *> TypeRef::getGenerics() { return this->generics; }
Param::Param(std::string name, TypeRef *type, Status generic)
    : name(name), type(type), status(generic) {
    assert(generic <= 1 && generic >= 0 && "Invalid param status");
} // clang-format off
bool BinaryOp::is_assignment(BinaryOp* p_node) {
    OpType p_op_type = p_node->op_type;

    return p_op_type == OpType::EQ || p_op_type == OpType::PLUSEQ ||
            p_op_type == OpType::MINUSEQ ||
            p_op_type == OpType::MULEQ || p_op_type == OpType::DIVEQ ||
            p_op_type == OpType::MOD_EQ ||
            p_op_type == OpType::BIT_LSHIFT_EQ ||
            p_op_type == OpType::BIT_RSHIFT_EQ ||
            p_op_type == OpType::BIT_OR_EQ ||
            p_op_type == OpType::BIT_AND_EQ ||
            p_op_type == OpType::BIT_XOR_EQ;
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

std::string FunctionCall::getArgumentsAsString(
    const std::vector<std::shared_ptr<types::Type>> args) {
    std::string result;
    for (auto arg = args.begin(); arg != args.end(); ++arg) {
        result += arg->get()->getPrettyName();
        if (arg != args.end() && args.size() != 1) {
            result += ", ";
        }
    }

    return result;
}

std::string GenericIdentifier::getNiceName() const {
    std::string gens = "<";

    int gIndex = 0;
    for (auto t : generics) {
        gens += t->getPrettyName();
        if (gIndex != (generics.size() - 1)) {
            gens += ", ";
        }

        gIndex++;
    }

    return identifier + (gIndex > 0 ? gens + ">" : "");
}

#define CASE(t, r)                                                             \
    case TokenType::t:                                                         \
        return r;
ConstantValue::ConstantType ConstantValue::deduceType(TokenType ty) {
    switch (ty) {
        CASE(VALUE_STRING, String)
        CASE(VALUE_CHAR, Char)
        CASE(VALUE_FLOAT, Float)
        CASE(VALUE_NUMBER, Number)
        CASE(VALUE_BOOL, Bool)

        default:
            E<BUG>(FMT("Unknown token type, coudn't deduce! (ty: %i)", ty));
    }

    UNREACHABLE
}
#undef CASE

std::string TypeRef::getPrettyName() const {
    std::string gens = "<";

    int gIndex = 0;
    for (auto t : generics) {
        gens += t->getPrettyName();
        if (gIndex != (generics.size() - 1)) {
            gens += ", ";
        }

        gIndex++;
    }

    return getName() + (gIndex > 0 ? gens + ">" : "");
}

} // namespace Expression
} // namespace Syntax
} // namespace snowball
