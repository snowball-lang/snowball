
#include "../DefinitveAssigment.h"

namespace snowball {
namespace Syntax {

SN_DEFINITE_ASSIGMENT_VISIT(Expression::ConstantValue) { }
SN_DEFINITE_ASSIGMENT_VISIT(Expression::TypeRef) { }
SN_DEFINITE_ASSIGMENT_VISIT(Expression::PseudoVariable) { }

SN_DEFINITE_ASSIGMENT_VISIT(Statement::TypeAlias) { }
SN_DEFINITE_ASSIGMENT_VISIT(Statement::ImportStmt) { }

} // namespace Syntax
} // namespace snowball
