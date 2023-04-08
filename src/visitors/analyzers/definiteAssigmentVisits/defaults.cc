
#include "../DefiniteAssigment.h"

namespace snowball {
namespace Syntax {

SN_DEFINITE_ASSIGMENT_VISIT(Expression::ConstantValue) {}
SN_DEFINITE_ASSIGMENT_VISIT(Expression::TypeRef) {}
SN_DEFINITE_ASSIGMENT_VISIT(Expression::BinaryOp) { assert(false); /*TODO:*/ }

SN_DEFINITE_ASSIGMENT_VISIT(Statement::VariableDecl) { /*TODO:*/ }
SN_DEFINITE_ASSIGMENT_VISIT(Statement::ImportStmt) {}

} // namespace Syntax
} // namespace snowball
