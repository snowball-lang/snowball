
#include "../errors/error.h"
#include "nodes.h"

#include <assert.h>
#include <string>
#include <vector>

namespace snowball {
namespace Syntax {
namespace Expression {

TypeRef::TypeRef(std::string p_name, ptr<snowball::DBGSourceInfo> p_dbg,
                 std::vector<TypeRef *> p_generics)
    : generics(p_generics), types::Type(REF, p_name) {
    setDBGInfo(p_dbg);
}

void TypeRef::setGenerics(std::vector<ptr<TypeRef>> g) { generics = g; }
std::vector<ptr<Expression::TypeRef>> GenericIdentifier::getGenerics() const {
    return generics;
}
std::vector<TypeRef *> TypeRef::getGenerics() { return this->generics; }

Param::Param(std::string name, TypeRef *type, Status generic)
    : name(name), type(type), status(generic) {
    assert(generic <= 1 && generic >= 0 && "Invalid param status");
}

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
        CASE(VALUE_NULL, Null)
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
