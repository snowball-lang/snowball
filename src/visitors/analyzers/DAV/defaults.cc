
#include "../DefinitveAssigment.h"

namespace snowball {
namespace Syntax {

SN_DEFINITE_ASSIGMENT_VISIT(Expression::ConstantValue) { }
SN_DEFINITE_ASSIGMENT_VISIT(Expression::TypeRef) { }
SN_DEFINITE_ASSIGMENT_VISIT(Expression::PseudoVariable) { }

// TODO: maybe loop flow should stop and identifier from being declared?
SN_DEFINITE_ASSIGMENT_VISIT(Statement::LoopFlow) { }
SN_DEFINITE_ASSIGMENT_VISIT(Statement::TypeAlias) { }
SN_DEFINITE_ASSIGMENT_VISIT(Statement::ImportStmt) { }
SN_DEFINITE_ASSIGMENT_VISIT(Statement::EnumTypeDef) { }

} // namespace Syntax
} // namespace snowball
